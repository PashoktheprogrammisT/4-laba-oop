cmake_minimum_required(VERSION 3.16)
project(FigureManagement)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(figure_management src/main.cpp)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(figure_management PRIVATE -Wall -Wextra)
endif()
