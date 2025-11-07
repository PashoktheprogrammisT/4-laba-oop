cmake_minimum_required(VERSION 3.16)
project(FigureManagement)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# Основная программа
add_executable(figure_management src/main.cpp)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(figure_management PRIVATE -Wall -Wextra)
endif()

# Настройка тестов
option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    # Поиск GoogleTest
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    )
    
    # Для Windows
    if(WIN32)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif()
    
    FetchContent_MakeAvailable(googletest)
    
    # Исполняемый файл для тестов
    add_executable(tests tests/test_figures.cpp)
    
    # Подключаем библиотеки
    target_link_libraries(tests PRIVATE GTest::gtest GTest::gtest_main)
    
    # Включаем тестирование
    include(GoogleTest)
    gtest_discover_tests(tests)
endif()
