cmake_minimum_required(VERSION 3.15)
project(Sokutei C)

set(CMAKE_C_STANDARD 90)

add_executable(counter_value_to_string counter_value_to_string.test.c)
add_test(NAME [unit]-counter-value-to-string COMMAND counter_value_to_string)

add_executable(create_counter create_counter.test.c)
add_test(NAME [unit]-create-counter COMMAND create_counter)

add_executable(create_counter_limit create_counter_limit.test.c)
add_test(NAME [unit]-create-counter-limit COMMAND create_counter_limit)

add_executable(csv_exporting csv_exporting.test.c)
add_test(NAME [unit]-csv-exporting COMMAND csv_exporting)

add_executable(float-counter float_counter.test.c)
add_test(NAME [unit]-float-counter COMMAND float-counter)

add_executable(integer-counter integer_counter.test.c)
add_test(NAME [unit]-integer-counter COMMAND integer-counter)

add_executable(json_exporting json_exporting.test.c)
add_test(NAME [unit]-json-exporting COMMAND json_exporting)

add_executable(string_function string_function.test.c)
add_test(NAME [unit]-string-function COMMAND string_function)

add_executable(errors errors.test.c)
add_test(NAME [unit]-errors COMMAND errors)

add_executable(timer_counter timer_counter.test.c)
add_test(NAME [unit]-timer-counter COMMAND timer_counter)

