cmake_minimum_required(VERSION 3.15)
project(Sokutei C)

set(CMAKE_C_STANDARD 90)

add_executable(counter_value_to_string src/counter_value_to_string.test.c )
add_test(NAME  counter_value_to_string COMMAND counter_value_to_string)

add_executable(create_counter-test src/create_counter.test.c )
add_test(NAME  create_counter-test COMMAND create_counter-test)

add_executable(create_counter_limit src/create_counter_limit.test.c)
add_test(NAME  create_counter_limit COMMAND create_counter_limit)

add_executable(csv_exporting src/csv_exporting.test.c )
add_test(NAME  csv_exporting COMMAND csv_exporting)

add_executable(float-counter src/float-counter.test.c )
add_test(NAME  float-counter COMMAND float-counter)

add_executable(integer-counter src/integer-counter.test.c)
add_test(NAME  integer-counter COMMAND integer-counter)

add_executable(json_exporting src/json_exporting.test.c )
add_test(NAME  json_exporting COMMAND json_exporting)

add_executable(string_function src/string_function.test.c )
add_test(NAME  string_function COMMAND string_function)

add_executable(errors src/errors.test.c )
add_test(NAME  errors COMMAND errors)

add_executable(timer_counter src/timer_counter.test.c)
add_test(NAME  timer_counter COMMAND timer_counter)

add_executable(ensure_counter src/ensure_counter.test.c)
add_test(NAME  ensure_counter COMMAND ensure_counter)

