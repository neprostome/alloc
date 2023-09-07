# CMake generated Testfile for 
# Source directory: /Users/denisbondarenko/Library/CloudStorage/OneDrive-ITMOUNIVERSITY/2sem/Prog/lab9/tests
# Build directory: /Users/denisbondarenko/Library/CloudStorage/OneDrive-ITMOUNIVERSITY/2sem/Prog/lab9/cmake-build-release/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[allocator_tests]=] "/Users/denisbondarenko/Library/CloudStorage/OneDrive-ITMOUNIVERSITY/2sem/Prog/lab9/cmake-build-release/bin/allocator_tests")
set_tests_properties([=[allocator_tests]=] PROPERTIES  _BACKTRACE_TRIPLES "/Users/denisbondarenko/Library/CloudStorage/OneDrive-ITMOUNIVERSITY/2sem/Prog/lab9/tests/CMakeLists.txt;41;add_test;/Users/denisbondarenko/Library/CloudStorage/OneDrive-ITMOUNIVERSITY/2sem/Prog/lab9/tests/CMakeLists.txt;0;")
add_test([=[allocator_benchmark]=] "/Users/denisbondarenko/Library/CloudStorage/OneDrive-ITMOUNIVERSITY/2sem/Prog/lab9/cmake-build-release/bin/allocator_benchmark")
set_tests_properties([=[allocator_benchmark]=] PROPERTIES  _BACKTRACE_TRIPLES "/Users/denisbondarenko/Library/CloudStorage/OneDrive-ITMOUNIVERSITY/2sem/Prog/lab9/tests/CMakeLists.txt;48;add_test;/Users/denisbondarenko/Library/CloudStorage/OneDrive-ITMOUNIVERSITY/2sem/Prog/lab9/tests/CMakeLists.txt;0;")
subdirs("../_deps/googletest-build")
subdirs("../_deps/benchmark-build")
