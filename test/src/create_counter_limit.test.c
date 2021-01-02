#include "../../greatest.h"
#include "../../sokutei.h"

TEST sokutei_add_counter_should_add_the_maximal_number_of_counters_without_error(void)
{
    //given
    char counter_name[2] ={'0', '\0'} ;
    const int expected = 0;
    int current;

    for (current = 0; current < SOKUTEI_MAX_COUNTER_COUNT; current++)
    {
        const int expected_number_of_counters = sokutei_number_of_counters + 1;

        //when
        const int actual = sokutei_add_counter(counter_name, SOKUTEI_INTEGER_TYPE);

        //then
        ASSERT_EQ(expected, actual);
        ASSERT_EQ(sokutei_number_of_counters, expected_number_of_counters);
        (*counter_name)++;
    }
    PASS();
}

TEST sokutei_add_counter_should_not_add_a_new_non_existing_counter_and_should_return_with_limit_reached_error(void)
{
    //given
    const char *counter_name = "a new counter";
    const int expected = SOKUTEI_COUNTER_LIMIT_REACHED;
    const int expected_number_of_counters = sokutei_number_of_counters;

    //when
    const int actual = sokutei_add_counter(counter_name, SOKUTEI_INTEGER_TYPE);

    //then
    ASSERT_EQ(expected, actual);
    ASSERT_EQ(sokutei_number_of_counters, expected_number_of_counters);
    PASS();
}

SUITE(create_counter_fail_test)
{
    RUN_TEST(sokutei_add_counter_should_add_the_maximal_number_of_counters_without_error);
    RUN_TEST(sokutei_add_counter_should_not_add_a_new_non_existing_counter_and_should_return_with_limit_reached_error);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv)
{
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(create_counter_fail_test);

    GREATEST_MAIN_END();
}
