#include <stdio.h>
#include <string.h>

#include "../../../greatest.h"


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

#define SOKUTEI_REPORTING_FORMAT 0
#include "../../../sokutei.h"

void reset_test(){
    buffer[0] = '\0';
    number_of_chars = 0;
    sokutei_number_of_counters = 0;
    sokutei_current_iteration = 0;
}


TEST integer_counter_altering_one_iteration_with_reporting_in_json(void)
{
    reset_test();
    int iterations = 7;
    const char *expected_output = "[{\"altering\":7}]";

    sokutei_create_integer_counter("altering");

    int index;
    sokutei_iteration_start();
    sokutei_json_begin_report();
    for(index = 0; index < iterations; index++){
        sokutei_integer_increment_counter("altering", 1);
    }
    sokutei_json_report_iteration();
    sokutei_iteration_finish();
    sokutei_json_end_report();

    ASSERT_EQ(0, strcmp(expected_output, buffer));
    ASSERT_EQ(sokutei_current_iteration, 1);
    PASS();
}

TEST integer_counter_altering_more_iterations_with_reporting_in_json(void)
{
    reset_test();
    int iterations = 4;
    const char *expected_output = "[{\"altering\":0},{\"altering\":1},{\"altering\":2},{\"altering\":3}]";

    sokutei_create_integer_counter("altering");

    int index;
    sokutei_iteration_start();
    sokutei_json_begin_report();
    for(index = 0; index < iterations; index++){
        sokutei_integer_increment_counter("altering", index);
        sokutei_json_report_iteration();
        sokutei_iteration_finish();
    }
    sokutei_json_end_report();

    printf("|%s|\n", buffer);

    ASSERT_EQ(0, strcmp(expected_output, buffer));
    ASSERT_EQ(sokutei_current_iteration, iterations);
    PASS();
}



SUITE(integer_counter_e2e) {
    RUN_TEST(integer_counter_altering_one_iteration_with_reporting_in_json);
    RUN_TEST(integer_counter_altering_more_iterations_with_reporting_in_json);
}


GREATEST_MAIN_DEFS();

int main(int argc, char **argv)
{
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(integer_counter_e2e);

    GREATEST_MAIN_END();
}
