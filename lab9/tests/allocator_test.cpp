#include "../include/memory_pool_allocator.h"

#include <gtest/gtest.h>

#include <vector>
#include <list>
#include <map>

TEST(MemoryPoolsAllocatorTest, AllocateAndDeallocate) {
    std::vector<std::pair<size_t, size_t>> pool_sizes = {{40, 3}};
    memory_pool_allocator<int> allocator(pool_sizes);

    int* block1 = allocator.allocate(1);
    ASSERT_NE(block1, nullptr);

    int* block2 = allocator.allocate(5);
    ASSERT_NE(block2, nullptr);

    int* block3 = allocator.allocate(3);
    ASSERT_NE(block3, nullptr);

    allocator.deallocate(block1, 1);
    allocator.deallocate(block2, 5);
    allocator.deallocate(block3, 3);
}

TEST(MemoryPoolsAllocatorTest, AllocateMoreThanPoolSize) {
    std::vector<std::pair<size_t, size_t>> pool_sizes = {{sizeof(int)+8, 5}};
    memory_pool_allocator<int> allocator(pool_sizes);

    int* blocks[6];
    for (int i = 0; i < 5; ++i) {
        blocks[i] = allocator.allocate(1);
        ASSERT_NE(blocks[i], nullptr);
    }
    ASSERT_THROW(blocks[5] = allocator.allocate(1), std::bad_alloc);

    for (int i = 0; i < 5; ++i) {
        allocator.deallocate(blocks[i], 1);
    }
}

TEST(MemoryPoolsAllocatorTest, AllocateAndDeallocateMultiplePools) {
    std::vector<std::pair<size_t, size_t>> pool_sizes = {{sizeof(int)+8, 5}, {(sizeof(double)+8)*2, 3}};
    memory_pool_allocator<int> allocator_int(pool_sizes);
    memory_pool_allocator<double> allocator_double(pool_sizes);

    int* block1 = allocator_int.allocate(1);
    ASSERT_NE(block1, nullptr);

    double* block2 = allocator_double.allocate(2);
    ASSERT_NE(block2, nullptr);

    allocator_int.deallocate(block1, 1);
    allocator_double.deallocate(block2, 2);
}

TEST(MemoryPoolsAllocatorTest, RebindAllocator) {
    std::vector<std::pair<size_t, size_t>> pool_sizes = {{std::max(sizeof(int), sizeof(double)), 5}};
    memory_pool_allocator<int> allocator_int(pool_sizes);
    memory_pool_allocator<double> allocator_double(pool_sizes);

    int* int_block = allocator_int.allocate(1);
    ASSERT_NE(int_block, nullptr);

    double* double_block = allocator_double.allocate(1);
    ASSERT_NE(double_block, nullptr);

    allocator_int.deallocate(int_block, 1);
    allocator_double.deallocate(double_block, 1);
}


TEST(MemoryPoolsAllocatorTest, MoveAllocator) {
    std::vector<std::pair<size_t, size_t>> pool_sizes = {{sizeof(int)+8, 5}};
    memory_pool_allocator<int> allocator1(pool_sizes);

    int* block1 = allocator1.allocate(1);
    ASSERT_NE(block1, nullptr);

    memory_pool_allocator<int> allocator2(std::move(allocator1));

    int* block2 = allocator2.allocate(1);
    ASSERT_NE(block2, nullptr);

    allocator2.deallocate(block1, 1);
    allocator2.deallocate(block2, 1);
}

TEST(MemoryPoolsAllocatorTest, MoveAssignAllocator) {
    std::vector<std::pair<size_t, size_t>> pool_sizes1 = {{sizeof(int), 5}};
    memory_pool_allocator<int> allocator1(pool_sizes1);

    std::vector<std::pair<size_t, size_t>> pool_sizes2 = {{sizeof(double), 3}};
    memory_pool_allocator<int> allocator2(pool_sizes2);

    int* block1 = allocator1.allocate(1);
    ASSERT_NE(block1, nullptr);

    int* block2 = allocator2.allocate(1);
    ASSERT_NE(block2, nullptr);

    allocator2.deallocate(block2, 1);

    allocator2 = std::move(allocator1);

    int* block3 = allocator2.allocate(1);
    ASSERT_NE(block3, nullptr);

    allocator2.deallocate(block1, 1);
    allocator2.deallocate(block3, 1);
}

TEST(MemoryPoolsAllocatorTest, CopyConstructor) {
    std::vector<std::pair<size_t, size_t>> pool_sizes = {{sizeof(int)*5, 3}};
    memory_pool_allocator<int> allocator1(pool_sizes);

    int* block1 = allocator1.allocate(1);
    ASSERT_NE(block1, nullptr);

    memory_pool_allocator<int> allocator2(allocator1);

    int* block2 = allocator2.allocate(1);
    ASSERT_NE(block2, nullptr);

    allocator1.deallocate(block1, 1);
    allocator2.deallocate(block2, 1);
}

TEST(MemoryPoolsAllocatorTest, CopyAssignmentOperator) {
    std::vector<std::pair<size_t, size_t>> pool_sizes1 = {{sizeof(int), 5}};
    memory_pool_allocator<int> allocator1(pool_sizes1);

    std::vector<std::pair<size_t, size_t>> pool_sizes2 = {{sizeof(double), 3}};
    memory_pool_allocator<int> allocator2(pool_sizes2);

    int* block1 = allocator1.allocate(1);
    ASSERT_NE(block1, nullptr);

    int* block2 = allocator2.allocate(1);
    ASSERT_NE(block2, nullptr);

    allocator2.deallocate(block2, 1);

    allocator2 = allocator1;

    int* block3 = allocator2.allocate(1);
    ASSERT_NE(block3, nullptr);

    allocator1.deallocate(block1, 1);
    allocator2.deallocate(block3, 1);
}

TEST(MemoryPoolsAllocatorTest, EqualityComparisonOperator) {
    std::vector<std::pair<size_t, size_t>> pool_sizes = {{sizeof(int)*5, 3}};
    memory_pool_allocator<int> allocator1(pool_sizes);
    memory_pool_allocator<int> allocator2(allocator1);

    ASSERT_TRUE(allocator1 == allocator2);
}

TEST(MemoryPoolsAllocatorTest, InequalityComparisonOperator) {
    std::vector<std::pair<size_t, size_t>> pool_sizes1 = {{sizeof(int)*5, 3}};
    memory_pool_allocator<int> allocator1(pool_sizes1);

    std::vector<std::pair<size_t, size_t>> pool_sizes2 = {{sizeof(double)*3, 2}};
    memory_pool_allocator<int> allocator2(pool_sizes2);

    ASSERT_TRUE(allocator1 != allocator2);
}

TEST(MemoryPoolsAllocatorTest, VectorAllocator) {
    std::vector<std::pair<size_t, size_t>> pools = {
            {sizeof(int) * 131072/100000, 2},
            {sizeof(int) * 131072/10000, 2},
            {sizeof(int) * 131072/1000, 2},
            {sizeof(int) * 131072/100, 2},
            {sizeof(int) * 131072/10, 2},
            {sizeof(int) * 131072, 2},
    };
    memory_pool_allocator<int> allocator(pools);

    std::vector<int, memory_pool_allocator<int>> v(allocator);

    for (int i = 0; i < 100000; ++i) {
        v.push_back(i);
    }

    for (int i = 0; i < 100000; ++i) {
        ASSERT_EQ(v[i], i);
    }
}

TEST(memory_pool_allocator, ListAllocator) {
    std::vector<std::pair<size_t, size_t>> pool_sizes = {{32, 5}};
    memory_pool_allocator<int> allocator(pool_sizes);

    std::list<int, memory_pool_allocator<int>> l(allocator);

    for (int i = 0; i < 5; ++i) {
        l.push_back(i);
    }

    int i = 0;
    for (auto it = l.begin(); it != l.end(); ++it, ++i) {
        ASSERT_EQ(*it, i);
    }
}

TEST(MemoryPoolsAllocatorTest, MapAllocator) {
    std::vector<std::pair<size_t, size_t>> pool_sizes = {{40, 5}};
    memory_pool_allocator<std::pair<const int, int>> allocator(pool_sizes);

    std::map<int, int, std::less<int>, memory_pool_allocator<std::pair<const int, int>>> m(allocator);

    for (int i = 0; i < 5; ++i) {
        m[i] = i;
    }

    for (int i = 0; i < 5; ++i) {
        ASSERT_EQ(m[i], i);
    }
}

TEST(MemoryPoolsAllocatorTest, MoveAssignSelf) {
    std::vector<std::pair<size_t, size_t>> pool_sizes = {{sizeof(int)+8, 5}};
    memory_pool_allocator<int> allocator(pool_sizes);

    int* block1 = allocator.allocate(1);
    ASSERT_NE(block1, nullptr);

    allocator = std::move(allocator);

    int* block2 = allocator.allocate(1);
    ASSERT_NE(block2, nullptr);

    allocator.deallocate(block1, 1);
    allocator.deallocate(block2, 1);
}
