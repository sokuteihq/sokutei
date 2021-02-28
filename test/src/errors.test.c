#include <stdio.h>
#include <string.h>

char buffer[1024] = {'\0'};
int number_of_chars = 0;

void print_char(const char c){
    buffer[number_of_chars++] = c;
    buffer[number_of_chars] = '\0';
}

void print_string(const char *string) {
    int index = 0;
    while(string[index]) {
        print_char(string[index++]);
    }
}

#define sokutei_print_char(char) print_char(char)
#define sokutei_print_string(string) print_string(string)

#include "../../greatest.h"
#include "../../sokutei.h"

void reset_test(){
    buffer[0] = '\0';
    number_of_chars = 0;
    sokutei_number_of_counters = 0;
    sokutei_current_iteration = 0;
}


TEST adding_invalid_type_should_produce_error_message(void)
{
    reset_test();
    //given
    const char *expected = "SOKUTEI ERROR: [Invalid type: MY_COUNTER]\n";
    const char *counter_name = "MY_COUNTER";
    const int invalid_counter_type = 127;

    //when
    sokutei_add_counter(counter_name, invalid_counter_type);

    //then
    ASSERT_EQ(0, strcmp(expected, buffer));
    PASS();
}

TEST reaching_maximal_number_of_counters_should_produce_error_message(void)
{
    reset_test();
    //given
    const char *expected = "SOKUTEI ERROR: [Counter limit reached: MY_COUNTER]\n";
    const char *counter_name = "MY_COUNTER";

    //when
    sokutei_number_of_counters = SOKUTEI_MAX_COUNTER_COUNT;
    sokutei_add_counter(counter_name, SOKUTEI_INTEGER_TYPE);

    //then
    ASSERT_EQ(0, strcmp(expected, buffer));
    PASS();
}

TEST adding_a_counter_twice_should_produce_error_message(void)
{
    reset_test();
    //given
    const char *expected = "SOKUTEI ERROR: [Counter already exists: MY_COUNTER]\n";
    const char *counter_name = "MY_COUNTER";

    //when
    sokutei_add_counter(counter_name, SOKUTEI_INTEGER_TYPE);
    sokutei_add_counter(counter_name, SOKUTEI_INTEGER_TYPE);

    //then
    ASSERT_EQ(0, strcmp(expected, buffer));
    PASS();
}


SUITE(error_output_tests)
{
    RUN_TEST(adding_invalid_type_should_produce_error_message);
    RUN_TEST(reaching_maximal_number_of_counters_should_produce_error_message);
    RUN_TEST(adding_a_counter_twice_should_produce_error_message);
}


GREATEST_MAIN_DEFS();

int main(int argc, char **argv)
{
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(error_output_tests);

    GREATEST_MAIN_END();
}
