#include "../include/memory_pool_allocator.h"

#include <benchmark/benchmark.h>

#include <iostream>
#include <list>
#include <vector>

static void CustomAllocatorListPushBack(benchmark::State& state) {
    const int num_elements = state.range(0);

    std::vector<std::pair<size_t, size_t>> pools = {{24, num_elements}};
    memory_pool_allocator<int> my_allocator(pools);

    for (auto _ : state) {
        std::list<int, memory_pool_allocator<int>> list(my_allocator);
        for (int i = 0; i < num_elements; ++i) {
            list.push_back(i);
        }
    }
}
BENCHMARK(CustomAllocatorListPushBack)->Arg(1000)->Arg(10000)->Arg(100000);

static void DefaultAllocatorListPushBack(benchmark::State& state) {
    const int num_elements = state.range(0);

    for (auto _ : state) {
        std::list<int, std::allocator<int>> list;
        for (int i = 0; i < num_elements; ++i) {
            list.push_back(i);
        }
    }
}
BENCHMARK(DefaultAllocatorListPushBack)->Arg(1000)->Arg(10000)->Arg(100000);

static void CustomAllocatorVectorPushBack(benchmark::State& state) {
    const int num_elements = state.range(0);

    std::vector<std::pair<size_t, size_t>> pools = {{24, num_elements}};
    memory_pool_allocator<int> my_allocator(pools);

    for (auto _ : state) {
        std::list<int, memory_pool_allocator<int>> list(my_allocator);
        for (int i = 0; i < num_elements; ++i) {
            list.push_back(i);
        }

    }
}
BENCHMARK(CustomAllocatorVectorPushBack)->Arg(1000)->Arg(10000)->Arg(100000);

static void DefaultAllocatorVectorPushBack(benchmark::State& state) {
    const int num_elements = state.range(0);

    for (auto _ : state) {
        std::list<int, std::allocator<int>> list;
        for (int i = 0; i < num_elements; ++i) {
            list.push_back(i);
        }
    }
}
BENCHMARK(DefaultAllocatorVectorPushBack)->Arg(1000)->Arg(10000)->Arg(100000);



BENCHMARK_MAIN();