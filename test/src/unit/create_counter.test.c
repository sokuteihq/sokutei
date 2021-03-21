#include "../../../greatest.h"
#include "../../../sokutei.h"

TEST sokutei_add_counter_should_add_a_new_non_existing_counter_and_return_without_any_error(void)
{
    //given
    const char *counter_name = "a new counter";
    const int expected = 0;
    const int expected_number_of_counters = sokutei_number_of_counters + 1;

    //when
    const int actual = sokutei_add_counter(counter_name, SOKUTEI_INTEGER_TYPE);

    //then
    ASSERT_EQ(expected, actual);
    ASSERT_EQ(sokutei_number_of_counters, expected_number_of_counters);
    PASS();
}

TEST sokutei_add_counter_should_not_add_an_existing_counter_and_should_return_with_an_already_exists_error(void)
{
    //given
    const char *counter_name = "a new counter 2";
    sokutei_add_counter(counter_name, SOKUTEI_INTEGER_TYPE);
    const int expected = SOKUTEI_COUNTER_ALREADY_EXISTS;
    const int expected_number_of_counters = sokutei_number_of_counters;

    //when
    const int actual = sokutei_add_counter(counter_name, SOKUTEI_INTEGER_TYPE);

    //then
    ASSERT_EQ(expected, actual);
    ASSERT_EQ(sokutei_number_of_counters, expected_number_of_counters);
    PASS();
}

TEST sokutei_add_counter_should_not_add_an_invalid_type_counter_and_should_return_with_a_not_matching_type_error(void)
{
    //given
    const char *counter_name = "name of the invalid counter";
    const int invalid_counter_type = 199;
    const int expected = SOKUTEI_NOT_MATCHING_TYPE;
    const int expected_number_of_counters = sokutei_number_of_counters;

    //when
    const int actual = sokutei_add_counter(counter_name, invalid_counter_type);

    //then
    ASSERT_EQ(expected, actual);
    ASSERT_EQ(sokutei_number_of_counters, expected_number_of_counters);
    PASS();
}

SUITE(create_counter_tests)
{
    RUN_TEST(sokutei_add_counter_should_add_a_new_non_existing_counter_and_return_without_any_error);
    RUN_TEST(sokutei_add_counter_should_not_add_an_existing_counter_and_should_return_with_an_already_exists_error);
    RUN_TEST(sokutei_add_counter_should_not_add_an_invalid_type_counter_and_should_return_with_a_not_matching_type_error);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv)
{
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(create_counter_tests);

    GREATEST_MAIN_END();
}
