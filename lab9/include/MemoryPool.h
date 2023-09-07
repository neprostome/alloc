#ifndef LAB9_MEMORYPOOl_H
#define LAB9_MEMORYPOOl_H

#include <iostream>
#include <stack>

class MemoryPool {
public:
    MemoryPool(size_t chunk_size, size_t pool_size) :
            chunk_size_(chunk_size), pool_size_(pool_size),
            pool_(nullptr) {
        pool_ = new char[chunk_size_ * pool_size_];
        AllocatePool();
    }

    ~MemoryPool() {
        delete[] pool_;
    }

    void* Alloc() {
        if (free_list_.empty()) {
            throw std::bad_alloc{};
        }

        Node* allocated_chunk = free_list_.top();
        free_list_.pop();
        return allocated_chunk;
    }

    void Free(void* ptr) {
        auto chunk = static_cast<Node*>(ptr);
        free_list_.push(chunk);
    }

    char* GetPool() const {
        return pool_;
    }

    size_t GetChunkSize() const {
        return chunk_size_;
    }

    size_t GetPoolSize() const {
        return pool_size_;
    }

    bool HasFreeSpace() const {
        return !free_list_.empty();
    }

private:
    size_t chunk_size_;
    size_t pool_size_;
    struct Node {
        Node* next;
    };
    char* pool_;
    std::stack<Node*> free_list_;

    void AllocatePool() {
        for (size_t i = 0; i < pool_size_; ++i) {
            auto node = reinterpret_cast<Node*>(pool_ + i * chunk_size_);
            free_list_.push(node);
        }
    }
};

#endif //LAB9_POOL_H