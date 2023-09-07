#ifndef LAB9_POOL_H
#define LAB9_POOL_H

#include <iostream>
#include <stack>

class memory_pool {
public:
    memory_pool(size_t chunk_size, size_t pool_size) :
            chunk_size_(chunk_size), pool_size_(pool_size),
            pool_(nullptr) {
        pool_ = new char[chunk_size_ * pool_size_];
        AllocatePool();
    }

    ~memory_pool() {
        delete[] pool_;
    }

    void* malloc() {
        if (free_list_.empty()) {
            throw std::bad_alloc{};
        }

        Node* allocated_chunk = free_list_.top();
        free_list_.pop();
        return allocated_chunk;
    }

    void free(void* ptr) {
        Node* chunk = static_cast<Node*>(ptr);
        free_list_.push(chunk);
    }

//    memory_pool(memory_pool&& other) noexcept :
//            chunk_size_(other.chunk_size_), pool_size_(other.pool_size_),
//            pool_(other.pool_), free_list_(other.free_list_) {
//        other.pool_ = nullptr;
//        other.free_list_ = nullptr;
//    }
//
//    memory_pool& operator=(memory_pool&& other) noexcept {
//        if (this != &other) {
//            delete[] pool_;
//
//            chunk_size_ = other.chunk_size_;
//            pool_size_ = other.pool_size_;
//            pool_ = other.pool_;
//            free_list_ = other.free_list_;
//
//            other.pool_ = nullptr;
//            other.free_list_ = nullptr;
//        }
//        return *this;
//    }

    bool HasFreeSpace() const {
        return !free_list_.empty();
    }

    size_t chunk_size_;
    size_t pool_size_;
//private:
    struct Node {
        Node* next;
    };

    char* pool_;
    std::stack<Node*> free_list_;

    void AllocatePool() {
        for (size_t i = 0; i < pool_size_; ++i) {
            Node* node = reinterpret_cast<Node*>(pool_ + i * chunk_size_);
            free_list_.push(node);
        }
    }

};

#endif //LAB9_POOL_H