#include "../../greatest.h"
#include "../../sokutei.h"

TEST sokutei_strcmp_tests(void) {

    ASSERT_EQ(sokutei_strcmp("", ""), 0);
    ASSERT_EQ(sokutei_strcmp("hello", "hello"), 0);
    ASSERT_EQ(sokutei_strcmp("hello", "HELLO"), 32);
    ASSERT_EQ(sokutei_strcmp("a", "b"), -1);

    PASS();
}

TEST sokutei_string_equals_tests(void) {

    ASSERT(sokutei_string_equals("", ""));
    ASSERT(sokutei_string_equals("counter_1", "counter_1"));

    ASSERT(!sokutei_string_equals("a", "b"));
    ASSERT(!sokutei_string_equals("counter_1234", "counter_1235"));
    ASSERT(!sokutei_string_equals("a string", "a longer string"));

    PASS();
}

TEST sokutei_strcpy_tests(void) {

    char * const test_string_1 = "";
    char test_buffer_1[SOKUTEI_MAX_COUNTER_NAME_LENGTH];
    sokutei_strcpy(test_buffer_1, test_string_1);
    ASSERT(sokutei_string_equals(test_buffer_1, test_string_1));


    char * const test_string_2 = "hello world";
    char test_buffer_2[SOKUTEI_MAX_COUNTER_NAME_LENGTH];
    sokutei_strcpy(test_buffer_2, test_string_2);
    ASSERT(sokutei_string_equals(test_buffer_2, test_string_2));


    char * const test_string_3 = "counter_1         .";
    char test_buffer_3[SOKUTEI_MAX_COUNTER_NAME_LENGTH];
    sokutei_strcpy(test_buffer_3, test_string_3);
    ASSERT(sokutei_string_equals(test_buffer_3, test_string_3));


    char * const test_string_4 = "some string, that is longer than SOKUTEI_MAX_COUNTER_NAME_LENGTH, to see if it's causing any error at runtime. It should cut the string at 'th|an'";
    char test_buffer_4[SOKUTEI_MAX_COUNTER_NAME_LENGTH];
    sokutei_strcpy(test_buffer_4, test_string_4);
    ASSERT(sokutei_string_equals(test_buffer_4, "some string, that is longer th"));


    char * const test_string_5 = "this should fit in the buffer.";
    char test_buffer_5[SOKUTEI_MAX_COUNTER_NAME_LENGTH];
    sokutei_strcpy(test_buffer_5, test_string_5);
    ASSERT(sokutei_string_equals(test_buffer_5, test_string_5));


    PASS();
}


TEST sokutei_add_counter_tests(void){
    char * const integer_counter_1 = "integer_counter_1";

    int index = sokutei_number_of_counters;
    const int SOME_INVALID_TYPE = 250;

    ASSERT_EQ(sokutei_add_counter(integer_counter_1, SOKUTEI_INTEGER_TYPE), index);
    ASSERT_EQ(sokutei_get_type_of(0), SOKUTEI_INTEGER_TYPE);
    ASSERT_EQ(sokutei_get_index_of_counter(integer_counter_1), index);
    ASSERT_EQ(sokutei_get_index_of_counter("__NOT_EXISTS__"), SOKUTEI_NOT_FOUND);
    index++;

    // adding the same counter again, should return error
    ASSERT_EQ(sokutei_add_counter(integer_counter_1, SOKUTEI_INTEGER_TYPE), SOKUTEI_COUNTER_ALREADY_EXISTS);
    ASSERT_EQ(sokutei_number_of_counters, index);

    // Adding an invalid type should return an error
    ASSERT_EQ(sokutei_add_counter(integer_counter_1, SOME_INVALID_TYPE), SOKUTEI_NOT_MATCHING_TYPE);
    ASSERT_EQ(sokutei_number_of_counters, index);


    char integer_counter_iterator[30];

    for(; index < SOKUTEI_MAX_COUNTER_COUNT - 1; ++index){
        sprintf(integer_counter_iterator, "counter_%d", index);
        ASSERT_EQ(sokutei_add_counter(integer_counter_iterator, SOKUTEI_INTEGER_TYPE), 0);
        ASSERT_EQ(sokutei_number_of_counters, index + 1);
    }
    sprintf(integer_counter_iterator, "counter_%d", index);
    ASSERT_EQ(sokutei_add_counter(integer_counter_iterator, SOKUTEI_INTEGER_TYPE), SOKUTEI_COUNTER_LIMIT_REACHED);
    ASSERT_EQ(sokutei_number_of_counters, index);

    PASS();
}

SUITE(the_suite) {
    RUN_TEST(sokutei_strcmp_tests);
    RUN_TEST(sokutei_string_equals_tests);
    RUN_TEST(sokutei_strcpy_tests);
    RUN_TEST(sokutei_add_counter_tests);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(the_suite);

    GREATEST_MAIN_END();
}
