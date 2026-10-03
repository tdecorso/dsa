cmake_minimum_required(VERSION 3.16)

project(dsa LANGUAGES C VERSION 0.1)

include_directories(include)

set(SRC_FILES src/error.c src/vector.c src/list.c)

add_library(dsa ${SRC_FILES})

add_executable(test_vector tests/test_vector.c)
add_executable(test_list tests/test_list.c)

target_link_libraries(test_vector PRIVATE dsa)
target_link_libraries(test_list   PRIVATE dsa)

enable_testing()

add_test(test_vector test_vector)
add_test(test_list   test_list)
