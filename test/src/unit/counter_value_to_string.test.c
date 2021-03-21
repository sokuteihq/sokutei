#include "../../greatest.h"
#include "../../sokutei.h"

TEST sokutei_integer_counter_to_string_should_convert_zero_to_string(void)
{
    //given
    const int input = 0;
    const char *expected = "0";
    char actual[20] = { 0 };

    //when
    sokutei_integer_counter_to_string(actual, input);


    //then
    ASSERT_EQ(0, strcmp(actual, expected));
    PASS();
}

TEST sokutei_integer_counter_to_string_should_convert_positive_number_1_to_string(void)
{
    //given
    const int input = 1;
    const char *expected = "1";
    char actual[20] = { 0 };

    //when
    sokutei_integer_counter_to_string(actual, input);


    //then
    ASSERT_EQ(0, strcmp(actual, expected));
    PASS();
}

TEST sokutei_integer_counter_to_string_should_convert_positive_number_125_to_string(void)
{
    //given
    const int input = 125;
    const char *expected = "125";
    char actual[20] = { 0 };

    //when
    sokutei_integer_counter_to_string(actual, input);


    //then
    ASSERT_EQ(0, strcmp(actual, expected));
    PASS();
}

TEST sokutei_integer_counter_to_string_should_convert_positive_number_2147483647_to_string(void)
{
    //given
    const int input = 2147483647;
    const char *expected = "2147483647";
    char actual[20] = { 0 };

    //when
    sokutei_integer_counter_to_string(actual, input);


    //then
    ASSERT_EQ(0, strcmp(actual, expected));
    PASS();
}

TEST sokutei_integer_counter_to_string_should_convert_negative_number_minus_1_to_string(void)
{
    //given
    const int input = -1;
    const char *expected = "-1";
    char actual[20] = { 0 };

    //when
    sokutei_integer_counter_to_string(actual, input);


    //then
    ASSERT_EQ(0, strcmp(actual, expected));
    PASS();
}

TEST sokutei_integer_counter_to_string_should_convert_negative_number_minus_125_to_string(void)
{
    //given
    const int input = -125;
    const char *expected = "-125";
    char actual[20] = { 0 };

    //when
    sokutei_integer_counter_to_string(actual, input);


    //then
    ASSERT_EQ(0, strcmp(actual, expected));
    PASS();
}

TEST sokutei_integer_counter_to_string_should_convert_negative_number_minus_2147483647_to_string(void)
{
    //given
    const int input = -2147483647;
    const char *expected = "-2147483647";
    char actual[20] = { 0 };

    //when
    sokutei_integer_counter_to_string(actual, input);


    //then
    ASSERT_EQ(0, strcmp(actual, expected));
    PASS();
}

SUITE(integer_counter_to_string_tests)
{
    RUN_TEST(sokutei_integer_counter_to_string_should_convert_zero_to_string);
    RUN_TEST(sokutei_integer_counter_to_string_should_convert_positive_number_1_to_string);
    RUN_TEST(sokutei_integer_counter_to_string_should_convert_positive_number_125_to_string);
    RUN_TEST(sokutei_integer_counter_to_string_should_convert_positive_number_2147483647_to_string);
    RUN_TEST(sokutei_integer_counter_to_string_should_convert_negative_number_minus_1_to_string);
    RUN_TEST(sokutei_integer_counter_to_string_should_convert_negative_number_minus_125_to_string);
    RUN_TEST(sokutei_integer_counter_to_string_should_convert_negative_number_minus_2147483647_to_string);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv)
{
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(integer_counter_to_string_tests);

    GREATEST_MAIN_END();
}
