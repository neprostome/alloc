cmake_minimum_required(VERSION 3.25)
project(include C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(include
        memory_pool_allocator.h
        MemoryPool.h)
