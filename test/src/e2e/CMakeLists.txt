cmake_minimum_required(VERSION 3.15)
project(Sokutei C)

set(CMAKE_C_STANDARD 90)

add_executable(integer-counter-e2e integer_counter.e2e.test.c)
add_test(NAME [e2e]-integer-counter COMMAND integer-counter-e2e)
