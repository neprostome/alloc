#ifndef LAB9_MEMORY_POOLS_ALLOCATOR_H
#define LAB9_MEMORY_POOLS_ALLOCATOR_H

#include "MemoryPool.h"

#include <cstddef>
#include <vector>
#include <map>

template <typename T>
class memory_pool_allocator {
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    template<typename U>
    struct rebind {
        using other = memory_pool_allocator<U>;
    };

    explicit memory_pool_allocator(const std::vector<std::pair<size_t, size_t>>& pool_sizes) noexcept {
        for (const auto& pool_size : pool_sizes) {
            auto new_pool = new MemoryPool(pool_size.first, pool_size.second);
            pools_[pool_size.first] = new_pool;
        }
    }

    ~memory_pool_allocator() {
        for (auto& pool : pools_) {
            delete pool.second;
        }
        pools_.clear();
    }

    memory_pool_allocator(const memory_pool_allocator& other) noexcept {
        for (const auto& pool : other.pools_) {
            auto new_pool = new MemoryPool(pool.second->GetChunkSize(), pool.second->GetPoolSize());
            pools_[pool.first] = new_pool;
        }
    }

    template<typename U>
    memory_pool_allocator(const memory_pool_allocator<U>& other) noexcept {
        for (const auto& pool : other.pools_) {
            auto new_pool = new MemoryPool(pool.second->GetChunkSize(), pool.second->GetPoolSize());
            pools_[pool.first] = new_pool;
        }
    }

    pointer allocate(size_type n) {
        size_type bytes_needed = n * sizeof(T);
        auto it = pools_.lower_bound(bytes_needed);
        auto end_it = pools_.end();
        if (it == end_it || !it->second->HasFreeSpace()) {
            throw std::bad_alloc();
        }
        auto p = static_cast<pointer>(it->second->Alloc());
        if (!p) {
            throw std::bad_alloc();
        }
        return p;
    }

    void deallocate(pointer p, size_type) {
        for (auto& pool : pools_) {
            if ((reinterpret_cast<char*>(p) >= pool.second->GetPool()) &&
                    (reinterpret_cast<char*>(p) < (pool.second->GetPool() +
                    pool.second->GetPoolSize() * pool.second->GetChunkSize()))) {
                pool.second->Free(p);
                return;
            }
        }
        throw std::invalid_argument("not found");
    }

    bool operator==(const memory_pool_allocator<T>& other) const noexcept {
        if (pools_.size() != other.pools_.size()) {
            return false;
        }
        for (const auto& pool : pools_) {
            auto it = other.pools_.find(pool.first);
            if (it == other.pools_.end()) {
                return false;
            }
            if (pool.second->GetChunkSize() != it->second->GetChunkSize() ||
                pool.second->GetPoolSize() != it->second->GetPoolSize()) {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const memory_pool_allocator<T>& other) const noexcept {
        return !(*this == other);
    }

    memory_pool_allocator<T>& operator=(const memory_pool_allocator<T>& other) noexcept {
        if (this != &other) {
            for (auto& pool : pools_) {
                delete pool.second;
            }
            pools_.clear();

            for (const auto& pool : other.pools_) {
                auto new_pool = new MemoryPool(pool.second->GetChunkSize(), pool.second->GetPoolSize());
                pools_[pool.first] = new_pool;
            }
        }
        return *this;
    }

    memory_pool_allocator(memory_pool_allocator<T>&& other) noexcept :
            pools_(std::move(other.pools_)) {};

    memory_pool_allocator<T>& operator=(memory_pool_allocator<T>&& other) noexcept {
        if (this != &other) {
            pools_ = std::move(other.pools_);
        }
        return *this;
    }

    std::map<size_t, MemoryPool*> pools_;
};

#endif //LAB9_MEMORY_POOLS_ALLOCATOR_H