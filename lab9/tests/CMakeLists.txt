include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz
)
FetchContent_Declare(
        benchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.6.0
)


FetchContent_MakeAvailable(googletest)
FetchContent_MakeAvailable(benchmark)

enable_testing()

add_executable(
        allocator_tests
        allocator_test.cpp
)

add_executable(
        allocator_benchmark
        allocator_benchmark.cpp
)

target_link_libraries(
        allocator_tests
        PRIVATE
        gtest_main
)

target_link_libraries(
        allocator_benchmark
        PRIVATE
        benchmark::benchmark
)

add_test(
        NAME
        allocator_tests
        COMMAND
        ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/allocator_tests
)

add_test(
        NAME
        allocator_benchmark
        COMMAND
        ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/allocator_benchmark
)