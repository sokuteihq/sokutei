#include "../../../greatest.h"
#include "../../../sokutei.h"

TEST float_get_counter_should_return_with_not_found_if_nonexist_counter_is_given(void) {
    //given
    const char *counter_name = "nonexist";
    const int expected = SOKUTEI_NOT_FOUND;

    //when
    const int actual = sokutei_get_float_counter("nonexist");

    //then
    ASSERT_EQ(expected, actual);
    PASS();
}


TEST float_get_counter_should_return_with_the_initial_value_zero_if_a_valid_counter_is_given(void) {
    //given
    const char *counter_name = "initial_value_is_zero";
    const SOKUTEI_FLOAT_COUNTER_TYPE expected = 0;

    //when
    sokutei_create_float_counter(counter_name);
    const SOKUTEI_FLOAT_COUNTER_TYPE actual = sokutei_get_float_counter(counter_name);

    //then
    ASSERT_EQ(expected, actual);
    PASS();
}


TEST float_get_counter_should_return_with_the_incremented_value(void) {
    //given
    const char *counter_name = "to increment";
    const SOKUTEI_FLOAT_COUNTER_TYPE expected = 1.0;

    //when
    sokutei_create_float_counter(counter_name);
    sokutei_increment_float_counter(counter_name);
    const SOKUTEI_FLOAT_COUNTER_TYPE actual = sokutei_get_float_counter(counter_name);

    //then
    ASSERT_EQ(expected, actual);
    PASS();
}


TEST float_get_counter_should_return_with_the_altered_value(void) {
    //given
    const char *counter_name = "to increment with n";
    const SOKUTEI_FLOAT_COUNTER_TYPE increment_with = 28.9;
    const SOKUTEI_FLOAT_COUNTER_TYPE expected = increment_with;

    //when
    sokutei_create_float_counter(counter_name);
    sokutei_alter_float_counter(counter_name, increment_with);
    const SOKUTEI_FLOAT_COUNTER_TYPE actual = sokutei_get_float_counter(counter_name);

    //then
    ASSERT_EQ(expected, actual);
    PASS();
}



SUITE(float_counter_tests) {
    RUN_TEST(float_get_counter_should_return_with_not_found_if_nonexist_counter_is_given);
    RUN_TEST(float_get_counter_should_return_with_the_initial_value_zero_if_a_valid_counter_is_given);
    RUN_TEST(float_get_counter_should_return_with_the_incremented_value);
    RUN_TEST(float_get_counter_should_return_with_the_altered_value);

}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(float_counter_tests);

    GREATEST_MAIN_END();
}
