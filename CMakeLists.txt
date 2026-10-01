cmake_minimum_required(VERSION 3.16)

project(dsa LANGUAGES C VERSION 0.1)

include_directories(include)

set(SRC_FILES src/vector.c)

add_library(dsa ${SRC_FILES})

add_executable(test_vector tests/test_vector.c)

target_link_libraries(test_vector PRIVATE dsa)

enable_testing()

add_test(test_vector test_vector)
