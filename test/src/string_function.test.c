#include "../../greatest.h"
#include "../../sokutei.h"

TEST sokutei_strcmp_should_return_zero_for_empty_inputs(void)
{
    // Given
    const char *input = "";
    const int expected = 0;

    // When
    const int actual = sokutei_strcmp(input, input);

    // Then
    ASSERT_EQ(actual, expected);
    FAIL();
}

TEST sokutei_strcmp_should_return_zero_for_non_empty_equal_inputs(void)
{
    //Given
    const char *input = "hello";
    const int expected = 0;

    //When
    const int actual = sokutei_strcmp(input, input);

    //Then
    ASSERT_EQ(actual, expected);
    PASS();
}

TEST sokutei_strcmp_should_return_non_zero_for_non_empty_equal_length_unequal_inputs(void)
{
    //Given
    const char *input_a = "hello";
    const char *input_b = "Hello";
    const int expected = 32;

    //When
    const int actual = sokutei_strcmp(input_a, input_b);

    //Then
    ASSERT_EQ(actual, expected);
    PASS();
}

TEST sokutei_strcmp_should_return_non_zero_for_substring(void)
{
    //Given
    const char *input = "aa";
    const char *substring_of_input = "a";
    const int expected = 97;

    //When
    const int actual = sokutei_strcmp(input, substring_of_input);

    //Then
    ASSERT_EQ(actual, expected);
    PASS();
}

SUITE(sokutei_strcmp_tests)
{
    RUN_TEST(sokutei_strcmp_should_return_zero_for_empty_inputs);
    RUN_TEST(sokutei_strcmp_should_return_zero_for_non_empty_equal_inputs);
    RUN_TEST(sokutei_strcmp_should_return_non_zero_for_non_empty_equal_length_unequal_inputs);
    RUN_TEST(sokutei_strcmp_should_return_non_zero_for_substring);
}

TEST sokutei_string_equals_should_return_true_on_empty_inputs(void)
{
    //Given
    const char *input = "";

    //When
    const int actual = sokutei_string_equals(input, input);

    //Then
    ASSERT(actual);
    PASS();
}

TEST sokutei_string_equals_should_return_true_on_equal_inputs(void)
{
    //Given
    const char *input = "counter_1";

    //When
    const int actual = sokutei_string_equals(input, input);

    //Then
    ASSERT(actual);
    PASS();
}

TEST sokutei_string_equals_should_return_false_on_equal_length_distinct_inputs(void)
{
    //Given
    const char *input_a = "a";
    const char *input_b = "b";

    //When
    const int actual = sokutei_string_equals(input_a, input_b);

    //Then
    ASSERT_FALSE(actual);
    PASS();
}

TEST sokutei_string_equals_should_return_false_on_equal_length_distinct_inputs_2(void)
{
    //Given
    const char *input_a = "counter_1234";
    const char *input_b = "counter_1235";

    //When
    const int actual = sokutei_string_equals(input_a, input_b);

    //Then
    ASSERT_FALSE(actual);
    PASS();
}

TEST sokutei_string_equals_should_return_false_on_distinct_inputs(void)
{
    //Given
    const char *input_a = "a string";
    const char *input_b = "a longer string";

    //When
    const int actual = sokutei_string_equals(input_a, input_b);

    //Then
    ASSERT_FALSE(actual);
    PASS();
}

SUITE(sokutei_string_equals_tests)
{
    RUN_TEST(sokutei_string_equals_should_return_true_on_empty_inputs);
    RUN_TEST(sokutei_string_equals_should_return_true_on_equal_inputs);
    RUN_TEST(sokutei_string_equals_should_return_false_on_equal_length_distinct_inputs);
    RUN_TEST(sokutei_string_equals_should_return_false_on_equal_length_distinct_inputs_2);
    RUN_TEST(sokutei_string_equals_should_return_false_on_distinct_inputs);
}

TEST sokutei_strcpy_should_produce_an_empty_string_on_empty_input(void)
{
    //given
    char test_buffer_1[SOKUTEI_MAX_COUNTER_NAME_LENGTH];
    char *const test_string_1 = "";

    //when
    sokutei_strcpy(test_buffer_1, test_string_1);

    //then
    ASSERT(sokutei_string_equals(test_buffer_1, test_string_1));
    PASS();
}

TEST sokutei_strcpy_should_copy_the_input_to_the_buffer_1(void)
{
    //given
    char test_buffer[SOKUTEI_MAX_COUNTER_NAME_LENGTH];
    char *const test_string = "hello world";

    //when
    sokutei_strcpy(test_buffer, test_string);

    //then
    ASSERT(sokutei_string_equals(test_buffer, test_string));
    PASS();
}

TEST sokutei_strcpy_should_copy_the_input_to_the_buffer_2(void)
{
    //given
    char test_buffer[SOKUTEI_MAX_COUNTER_NAME_LENGTH];
    char *const test_string = "counter_1         .";

    //when
    sokutei_strcpy(test_buffer, test_string);

    //then
    ASSERT(sokutei_string_equals(test_buffer, test_string));
    PASS();
}

TEST sokutei_strcpy_should_copy_only_the_maximum_number_of_characters(void)
{
    //given
    char test_buffer[SOKUTEI_MAX_COUNTER_NAME_LENGTH];
    char *const test_string = "some string, that is longer than SOKUTEI_MAX_COUNTER_NAME_LENGTH, to see if it's causing any error at runtime. It should cut the string at 'th|an'";
    char *expected = "some string, that is longer th";

    //when
    sokutei_strcpy(test_buffer, test_string);

    //then
    ASSERT(sokutei_string_equals(test_buffer, expected));
    PASS();
}

TEST sokutei_strcpy_should_copy_all_characters_of_a_maximum_length_input(void)
{
    //given
    char test_buffer[SOKUTEI_MAX_COUNTER_NAME_LENGTH];
    char *const input = "this should fit in the buffer.";
    char *const expected = input;

    //when
    sokutei_strcpy(test_buffer, input);

    //then
    ASSERT(sokutei_string_equals(test_buffer, expected));
    PASS();
}

SUITE(sokutei_strcpy_tests)
{
    RUN_TEST(sokutei_strcpy_should_produce_an_empty_string_on_empty_input);
    RUN_TEST(sokutei_strcpy_should_copy_the_input_to_the_buffer_1);
    RUN_TEST(sokutei_strcpy_should_copy_the_input_to_the_buffer_2);
    RUN_TEST(sokutei_strcpy_should_copy_only_the_maximum_number_of_characters);
    RUN_TEST(sokutei_strcpy_should_copy_all_characters_of_a_maximum_length_input);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv)
{
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(sokutei_strcmp_tests);
    RUN_SUITE(sokutei_string_equals_tests);
    RUN_SUITE(sokutei_strcpy_tests);

    GREATEST_MAIN_END();
}
