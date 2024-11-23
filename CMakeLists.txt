cmake_minimum_required(VERSION 3.20)
project(homework LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

add_compile_options(-Wall -Wextra)

add_subdirectory(homework_2)
add_subdirectory(homework_3)
