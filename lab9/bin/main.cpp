#include "../include/memory_pool.h"
#include "../include/memory_pool_allocator.h"

#include <chrono>
#include <iostream>
#include <vector>
#include <list>


int main() {

    const int numElements = 10000000;
//    int pool_size = static_cast<int>(pow(2, ceil(log2(numElements + 1))) * 4);
//
//    std::vector<std::pair<size_t, size_t>> pools = {
//            {pool_size/1000000, 2},
//            {pool_size/100000, 2},
//            {pool_size/10000, 2},
//            {pool_size/1000, 2},
//            {pool_size/100, 2},
//            {pool_size/10, 2},
//            {pool_size, 2},
//    };
//
//
//    MemoryPoolsAllocator<int> customAllocator(pools);
////    std::vector<int, MemoryPoolsAllocator<int>> my_vector(customAllocator);
//


//    const int numElements = 100000000;
//    int pool_size = static_cast<int>(pow(2, ceil(log2(numElements + 1))) * 4);
//
//    std::vector<std::pair<size_t, size_t>> pools = {
//            {pool_size/1000000, pool_size/1000000},
//            {pool_size/100000, pool_size/100000},
//            {pool_size/10000, pool_size/10000},
//            {pool_size/1000, pool_size/1000},
//            {pool_size/100, pool_size/100},
//            {pool_size/10, pool_size/10},
//            {pool_size, pool_size},
//    };
//
//
//    MemoryPoolsAllocator<int> customAllocator(pools);
//    std::vector<int, MemoryPoolsAllocator<int>> customVec(customAllocator);
//
//
//    auto start = std::chrono::high_resolution_clock::now();
//    for (int i = 0; i < numElements; ++i) {
//        customVec.push_back(i);
//    }
//    auto end = std::chrono::high_resolution_clock::now();
//    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//    std::cout << "Custom allocator time: " << elapsed << " ms\n";
//
//    start = std::chrono::high_resolution_clock::now();
//    std::vector<int, std::allocator<int>> defaultVec(defaultAllocator);
//    for (int i = 0; i < numElements; ++i) {
//        defaultVec.push_back(i);
//    }
//    end = std::chrono::high_resolution_clock::now();
//    elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//    std::cout << "Default allocator time: " << elapsed << " ms\n";

    // List test with custom allocator
    std::vector<std::pair<size_t, size_t>> pools = {{24, numElements}};


    memory_pool_allocator<int> customAllocator(pools);
    std::allocator<int> defaultAllocator;
    auto start = std::chrono::high_resolution_clock::now();
    std::list<int, memory_pool_allocator<int>> customList(customAllocator);
    for (int i = 0; i < numElements; ++i) {
        customList.push_back(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Custom allocator (list) time: " << elapsed << " ms\n";

    // List test with default allocator
    start = std::chrono::high_resolution_clock::now();
    std::list<int, std::allocator<int>> defaultList(defaultAllocator);
    for (int i = 0; i < numElements; ++i) {
        defaultList.push_back(i);
    }
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Default allocator (list) time: " << elapsed << " ms\n";

    return 0;
}

