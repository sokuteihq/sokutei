cmake_minimum_required(VERSION 3.15)
project(Sokutei C)

set(CMAKE_C_STANDARD 90)

include(CTest)

add_subdirectory(src/unit)
add_subdirectory(src/e2e)
