cmake_minimum_required(VERSION 3.29)
project(bf C)

set(CMAKE_C_STANDARD 11)
add_compile_options(-Wall -Werror -Wextra -Wpedantic)
add_executable(bf
    bf.c)
