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

#define SOKUTEI_REPORTING_FORMAT 1
#include "../../../sokutei.h"

void reset_test(){
    buffer[0] = '\0';
    number_of_chars = 0;
    sokutei_number_of_counters = 0;
    sokutei_current_iteration = 0;
}

TEST sokutei_begin_report_should_create_csv_report_header_with_one_counter(void)
{
    reset_test();
    //given
    const char *counter_name = "a new counter";
    sokutei_add_counter(counter_name, SOKUTEI_INTEGER_TYPE);
    const char *expected = "a new counter\n";

    //when
    sokutei_begin_report();

    //then
    ASSERT_EQ(0, strcmp(expected, buffer));
    PASS();
}

TEST sokutei_begin_report_should_create_csv_report_header_with_three_counters(void)
{
    reset_test();
    //given
    sokutei_add_counter("a", SOKUTEI_INTEGER_TYPE);
    sokutei_add_counter("b", SOKUTEI_INTEGER_TYPE);
    sokutei_add_counter("c", SOKUTEI_INTEGER_TYPE);
    const char *expected = "a,b,c\n";

    //when
    sokutei_begin_report();

    //then
    ASSERT_EQ(0, strcmp(expected, buffer));
    PASS();
}


TEST sokutei_begin_report_should_create_csv_report_with_one_counter(void)
{
    reset_test();
    //given

    sokutei_add_counter("a", SOKUTEI_INTEGER_TYPE);
    const char *expected = "a\n0\n";

    //when
    sokutei_begin_report();
    sokutei_report_iteration();

    //then
    ASSERT_EQ(0, strcmp(expected, buffer));
    PASS();
}



TEST sokutei_begin_report_should_create_csv_report_with_three_counters(void)
{
    reset_test();
    //given

    sokutei_add_counter("a", SOKUTEI_INTEGER_TYPE);
    sokutei_add_counter("b", SOKUTEI_INTEGER_TYPE);
    sokutei_add_counter("c", SOKUTEI_INTEGER_TYPE);
    const char *expected = "a,b,c\n0,0,0\n";

    //when
    sokutei_begin_report();
    sokutei_report_iteration();

    printf("|%s|", buffer);
    //then
    ASSERT_EQ(0, strcmp(expected, buffer));
    PASS();
}

TEST sokutei_begin_report_should_create_full_csv_report_for_two_iterations_with_three_counters(void)
{
    reset_test();
    //given

    sokutei_add_counter("a", SOKUTEI_INTEGER_TYPE);
    sokutei_add_counter("b", SOKUTEI_INTEGER_TYPE);
    sokutei_add_counter("c", SOKUTEI_INTEGER_TYPE);
    const char *expected = "a,b,c\n0,0,0\n0,0,0\n";

    //when
    sokutei_begin_report();
    sokutei_report_iteration();
    sokutei_iteration_finish();
    sokutei_report_iteration();
    sokutei_end_report();

    //then
    ASSERT_EQ(0, strcmp(expected, buffer));
    PASS();
}

SUITE(create_counter_tests)
{
    RUN_TEST(sokutei_begin_report_should_create_csv_report_header_with_one_counter);
    RUN_TEST(sokutei_begin_report_should_create_csv_report_header_with_three_counters);
    RUN_TEST(sokutei_begin_report_should_create_csv_report_with_one_counter);
    RUN_TEST(sokutei_begin_report_should_create_csv_report_with_three_counters);
    RUN_TEST(sokutei_begin_report_should_create_full_csv_report_for_two_iterations_with_three_counters);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv)
{
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(create_counter_tests);

    GREATEST_MAIN_END();
}
