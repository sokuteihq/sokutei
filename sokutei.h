#ifndef SOKUTEI_BENCHMARK_H
#define SOKUTEI_BENCHMARK_H

/// Determine operating system
#ifndef SOKUTEI_OS_TYPE

#define SOKUTEI_LINUX 1
#define SOKUTEI_WINDOWS 2
#define SOKUTEI_MACOS 3
#define SOKUTEI_ARDUINO 4

#if defined(linux) || defined(_linux) || defined(__linux__) || defined(__unix__) // Linux
#   define SOKUTEI_OS_TYPE SOKUTEI_LINUX
#elif defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS) || defined(__WINDOWS__) // Windows
#   define SOKUTEI_OS_TYPE SOKUTEI_WINDOWS
#elif (defined(__MACH__) && defined(__APPLE__)) // MacOs
#   define SOKUTEI_OS_TYPE SOKUTEI_MACOS
#elif defined(ARDUINO) // Arduino
#   define SOKUTEI_OS_TYPE SOKUTEI_ARDUINO
#endif

#ifndef SOKUTEI_SOKUTEI_COMMON_H
#define SOKUTEI_SOKUTEI_COMMON_H

void sokutei_print_error(const char *error_message, const char *error_param );

#endif //SOKUTEI_SOKUTEI_COMMON_H


#if (defined(__NVCC__))

    typedef struct couter_type{
        cudaEvent_t start;
        cudaEvent_t stop;
        unsigned int elapsed;
    } CUDA_TIMER_TYPE;


    SOKUTEI_TIMER_TYPE *sokutei_get_timer_counter(const char *);

    void cuda_timer_start_function(char *counter_name){
        SOKUTEI_TIMER_TYPE *counter = sokutei_get_timer_counter(counter_name);
        cudaEventCreate(&(counter->start));
        cudaEventCreate(&(counter->stop));
        cudaEventRecord(counter->start);
    }

    void cuda_timer_stop_function(char *counter_name){
        SOKUTEI_TIMER_TYPE *counter = sokutei_get_timer_counter(counter_name);
        cudaEventRecord(counter->stop);
        cudaEventSynchronize(counter->stop);
        cudaEventElapsedTime(&(counter->elapsed), counter->start, counter->stop);
    }

#   ifndef SOKUTEI_TIMER_COUNTER_TYPE
#       define SOKUTEI_TIMER_COUNTER_TYPE CUDA_TIMER_TYPE
#   endif

#   ifndef SOKUTEI_TIMER_START
#       define SOKUTEI_TIMER_START cuda_timer_start_function
#   endif

#   ifndef SOKUTEI_TIMER_STOP
#       define SOKUTEI_TIMER_STOP cuda_timer_stop_function
#   endif

#   ifndef SOKUTEI_CUSTOM_TIMER
#   endif //SOKUTEI_CUSTOM_TIMER

#endif //CONDITIONAL

#if SOKUTEI_OS_TYPE == SOKUTEI_WINDOWS

#ifndef SOKUTEI_SOKUTEI_PLATFORM_H
#define SOKUTEI_SOKUTEI_PLATFORM_H

#   include <stdio.h>

#   ifndef sokutei_print_string
#       define sokutei_print_string(string) printf("%s", string);
#   endif

#   include <time.h>

    typedef struct counter_type {
        clock_t elapsed;
        clock_t last_start;
    } SOKUTEI_TIMER_TYPE;

    SOKUTEI_TIMER_TYPE *sokutei_get_timer_counter(const char *);

    void sokutei_timer_start_function(char *counter_name){
        SOKUTEI_TIMER_TYPE *counter = sokutei_get_timer_counter(counter_name);
        counter->last_start = clock();
    }

    void sokutei_timer_stop_function(char *counter_name){
        SOKUTEI_TIMER_TYPE *counter = sokutei_get_timer_counter(counter_name);
        counter->elapsed += clock() - counter->last_start;
        counter->last_start = 0;
    }

#   ifndef SOKUTEI_CUSTOM_TIMER
#   endif //SOKUTEI_CUSTOM_TIMER
#endif //CONDITIONAL
#endif //SOKUTEI_SOKUTEI_PLATFORM_H

#if SOKUTEI_OS_TYPE == SOKUTEI_LINUX

#ifndef SOKUTEI_SOKUTEI_PLATFORM_H
#define SOKUTEI_SOKUTEI_PLATFORM_H

#   include <stdio.h>

#   ifndef sokutei_print_string
#       define sokutei_print_string(string) printf("%s", string);
#   endif


#   include <time.h>

    typedef struct counter_type {
        clock_t elapsed;
        clock_t last_start;
    } SOKUTEI_TIMER_TYPE;

    SOKUTEI_TIMER_TYPE *sokutei_get_timer_counter(const char *);

    void sokutei_timer_start_function(char *counter_name){
        SOKUTEI_TIMER_TYPE *counter = sokutei_get_timer_counter(counter_name);
        counter->last_start = clock();
    }

    void sokutei_timer_stop_function(char *counter_name){
        SOKUTEI_TIMER_TYPE *counter = sokutei_get_timer_counter(counter_name);
        counter->elapsed += clock() - counter->last_start;
        counter->last_start = 0;
    }

#   ifndef SOKUTEI_CUSTOM_TIMER
#   endif //SOKUTEI_CUSTOM_TIMER
#endif //CONDITIONAL
#endif //SOKUTEI_SOKUTEI_PLATFORM_H

#if SOKUTEI_OS_TYPE == SOKUTEI_MACOS

#ifndef SOKUTEI_SOKUTEI_PLATFORM_H
#define SOKUTEI_SOKUTEI_PLATFORM_H

#   include <stdio.h>

#   ifndef sokutei_print_string
#       define sokutei_print_string(string) printf("%s", string);
#   endif


#   ifndef SOKUTEI_CUSTOM_TIMER
#   endif //SOKUTEI_CUSTOM_TIMER
#endif //CONDITIONAL
#endif //SOKUTEI_SOKUTEI_PLATFORM_H

#if SOKUTEI_OS_TYPE == SOKUTEI_ARDUINO

#ifndef SOKUTEI_SOKUTEI_PLATFORM_H
#define SOKUTEI_SOKUTEI_PLATFORM_H

#   ifndef sokutei_print_string
#       define sokutei_print_string(string) Serial.print(string)
#   endif


    typedef struct counter_type {
        unsigned long elapsed;
        unsigned long last_start;
    } SOKUTEI_TIMER_TYPE;


    SOKUTEI_TIMER_TYPE *sokutei_get_timer_counter(const char *);

    void sokutei_timer_start_function(char *counter_name){
        SOKUTEI_TIMER_TYPE *counter = sokutei_get_timer_counter(counter_name);
        counter->last_start = millis();
    }

    void sokutei_timer_stop_function(char *counter_name){
        SOKUTEI_TIMER_TYPE *counter = sokutei_get_timer_counter(counter_name);
        counter->elapsed += millis() - counter->last_start;
        counter->last_start = 0;
    }

#   ifndef SOKUTEI_CUSTOM_TIMER
#   endif //SOKUTEI_CUSTOM_TIMER
#endif //CONDITIONAL
#endif //SOKUTEI_SOKUTEI_PLATFORM_H




#ifndef SOKUTEI_TIMER_COUNTER_TYPE
#   define SOKUTEI_TIMER_COUNTER_TYPE SOKUTEI_TIMER_TYPE
#endif

#ifndef SOKUTEI_TIMER_START
#   define SOKUTEI_TIMER_START sokutei_timer_start_function
#endif

#ifndef SOKUTEI_TIMER_STOP
#   define SOKUTEI_TIMER_STOP sokutei_timer_stop_function
#endif

#endif
///--- Determine operating system

#define SOKUTEI_MAX_COUNTER_COUNT  100
#define SOKUTEI_MAX_COUNTER_NAME_LENGTH 30

#define SOKUTEI_COUNTER_TO_STRING_BUFFER_LENGTH 64
#define SOKUTEI_COUNTER_TO_STRING_PRECISION 15

#define SOKUTEI_INTEGER_COUNTER_TYPE int
#define SOKUTEI_FLOAT_COUNTER_TYPE double


#define MAX_SIZE_OF_TYPES   ((sizeof(SOKUTEI_INTEGER_COUNTER_TYPE) > sizeof(SOKUTEI_FLOAT_COUNTER_TYPE)) \
                            ? ((sizeof(SOKUTEI_INTEGER_COUNTER_TYPE) > sizeof(SOKUTEI_TIMER_COUNTER_TYPE)) \
                                ? sizeof(SOKUTEI_INTEGER_COUNTER_TYPE) \
                                : sizeof(SOKUTEI_TIMER_COUNTER_TYPE))\
                            : ((sizeof(SOKUTEI_FLOAT_COUNTER_TYPE) > sizeof(SOKUTEI_TIMER_COUNTER_TYPE)) \
                                ? sizeof(SOKUTEI_FLOAT_COUNTER_TYPE) \
                                : sizeof(SOKUTEI_TIMER_COUNTER_TYPE)))

#define SOKUTEI_INTEGER_TYPE '1'
#define SOKUTEI_FLOAT_TYPE '2'
#define SOKUTEI_INTERVAL_TYPE '3'

#define SOKUTEI_NOT_FOUND -1
#define SOKUTEI_NOT_MATCHING_TYPE -2
#define SOKUTEI_COUNTER_LIMIT_REACHED -3
#define SOKUTEI_COUNTER_ALREADY_EXISTS -4

/**
 * Padding sets the number of bytes to separate names from type indicators, do we need to separate the type indicator with its own string terminator?
 */
#define SOKUTEI_TYPE_INDICATOR_PADDING 2

/**
 * SOKUTEI_TYPE_INDICATOR_INDEX is the index of the type indicator, which is positioned after the counter name's maximal index.
 */
#define SOKUTEI_TYPE_INDICATOR_INDEX (SOKUTEI_MAX_COUNTER_NAME_LENGTH + 1)


#ifdef SOKUTEI_LOGGING_ENABLED
#define SOKUTEI_DEBUG_PRINT(x, y) printf(x, y)
#else
#define SOKUTEI_DEBUG_PRINT(x, y)
#endif



/// String functions

int sokutei_strcmp(const char *string_a, const char *string_b){
    int i = 0;
    while(string_a[i] == string_b[i] && string_a[i]) i++;
    return string_a[i] - string_b[i];
}


char *sokutei_strcpy(char *string_a, const char *string_b){
    int i;
    for(i = 0; (string_a[i] = string_b[i]) && (i < SOKUTEI_MAX_COUNTER_NAME_LENGTH); i++);
    string_a[SOKUTEI_MAX_COUNTER_NAME_LENGTH] = '\0';
    return string_a;
}


#define sokutei_string_equals(string_a, string_b) (sokutei_strcmp(string_a, string_b) == 0)


int sokutei_integer_counter_to_string(char *target_buffer, SOKUTEI_INTEGER_COUNTER_TYPE integer){
    char local_buffer[SOKUTEI_COUNTER_TO_STRING_BUFFER_LENGTH + 1] = {'\0'};
    int index = SOKUTEI_COUNTER_TO_STRING_BUFFER_LENGTH;
    int length = 0;
    if(integer < 0){
        target_buffer[0] = '-';
        length = 1;
        integer *= -1;
    }

    do{
        local_buffer[index--] = '0' + (integer % 10);
        integer /= 10;
    } while(integer);

    index++;

    while(index <= SOKUTEI_COUNTER_TO_STRING_BUFFER_LENGTH){
        target_buffer[length++] = local_buffer[index++];
    }
    return length;
}


int sokutei_float_counter_to_string(char *target_buffer, SOKUTEI_FLOAT_COUNTER_TYPE floating_point){
    int digits = 0;
    SOKUTEI_INTEGER_COUNTER_TYPE integer_part = floating_point;
    floating_point -= integer_part;
    digits = sokutei_integer_counter_to_string(target_buffer, integer_part);

    target_buffer[digits++] = '.';
    int precision;
    for (precision = 0; precision < SOKUTEI_COUNTER_TO_STRING_PRECISION - 1; precision++){
        floating_point *= 10;
        integer_part = (SOKUTEI_INTEGER_COUNTER_TYPE) floating_point;
        floating_point -= integer_part;
        digits += sokutei_integer_counter_to_string(target_buffer + digits, integer_part) ;
    }
    integer_part = floating_point *= 10;

    return digits;
}


void sokutei_error_counter_to_string(){
}

///--- String functions


/// Counters

/**
 * sokutei_counter_definitions is an array, which consists of the counter name followed by string terminator (\0), and the type of the counter.
 */
char sokutei_counter_definitions[SOKUTEI_MAX_COUNTER_COUNT][SOKUTEI_MAX_COUNTER_NAME_LENGTH + SOKUTEI_TYPE_INDICATOR_PADDING] = {'\0'};

char sokutei_counters[SOKUTEI_MAX_COUNTER_COUNT * MAX_SIZE_OF_TYPES] = {0};
int sokutei_number_of_counters = 0;

#define sokutei_get_counter_name_at_index(index) sokutei_counter_definitions[index]
#define sokutei_counter_at_index(type, index) (type *)(sokutei_counters + (index * MAX_SIZE_OF_TYPES))

char sokutei_get_type_of(const int index){
    return sokutei_counter_definitions[index][SOKUTEI_TYPE_INDICATOR_INDEX];
}


int sokutei_get_index_of_counter(const char *counter_name){
    int i;
    for(i = 0; i < sokutei_number_of_counters; i++){
        if(sokutei_string_equals(sokutei_counter_definitions[i], counter_name)){
            return i;
        }
    }
    return SOKUTEI_NOT_FOUND;
}


inline int sokutei_is_unknown_counter_type(const char type){
    return !(type == SOKUTEI_INTEGER_TYPE || type == SOKUTEI_FLOAT_TYPE || type == SOKUTEI_INTERVAL_TYPE);
}


inline int sokutei_is_counter_limit_reached(){
    return sokutei_number_of_counters >= SOKUTEI_MAX_COUNTER_COUNT;
}


inline int sokutei_create_new_counter(const char *counter_name, const char type){
    sokutei_strcpy(sokutei_counter_definitions[sokutei_number_of_counters], counter_name);
    sokutei_counter_definitions[sokutei_number_of_counters][SOKUTEI_TYPE_INDICATOR_INDEX] = type;
    sokutei_number_of_counters++;
    return 0;
}


int sokutei_add_counter(const char *counter_name, const char type){
    if(sokutei_is_unknown_counter_type(type)){
        sokutei_print_error("Invalid type: ", counter_name);
        return SOKUTEI_NOT_MATCHING_TYPE;
    }

    if(sokutei_is_counter_limit_reached()){
        sokutei_print_error("Counter limit reached: ", counter_name);
        return SOKUTEI_COUNTER_LIMIT_REACHED;
    }

    if(sokutei_get_index_of_counter(counter_name) != SOKUTEI_NOT_FOUND){
        sokutei_print_error("Counter already exists: ", counter_name);
        return SOKUTEI_COUNTER_ALREADY_EXISTS;
    }

    return sokutei_create_new_counter(counter_name, type);
}


int sokutei_ensure_counter(const char *counter_name, const char type){
    if(sokutei_is_unknown_counter_type(type)){
        sokutei_print_error("Invalid type: ", counter_name);
        return SOKUTEI_NOT_MATCHING_TYPE;
    }

    if(sokutei_is_counter_limit_reached()){
        sokutei_print_error("Counter limit reached: ", counter_name);
        return SOKUTEI_COUNTER_LIMIT_REACHED;
    }

    if(sokutei_get_index_of_counter(counter_name) == SOKUTEI_NOT_FOUND) {
        return sokutei_create_new_counter(counter_name, type);
    }
    return 0;
}
///--- Counters



/// Iterations

int sokutei_current_iteration = 0;


void sokutei_iteration_finish_handler(){
    int index;
    for(index = 0; index < (SOKUTEI_MAX_COUNTER_COUNT * MAX_SIZE_OF_TYPES); index++){
        sokutei_counters[index] = 0;
    }
    sokutei_current_iteration++;
}

///--- Iterations


/// Integer counter functions
SOKUTEI_INTEGER_COUNTER_TYPE sokutei_integer_get_counter(const char *counter_name){
    const int index = sokutei_get_index_of_counter(counter_name);

    if(index == SOKUTEI_NOT_FOUND){
        sokutei_print_error("(sokutei_integer_get_counter) Counter not found with name: ", counter_name);
        return SOKUTEI_NOT_FOUND;
    }
    if(sokutei_get_type_of(index) != SOKUTEI_INTEGER_TYPE){
        sokutei_print_error("(sokutei_integer_get_counter) Counter is not of SOKUTEI_INTEGER type: ", counter_name);
        return SOKUTEI_NOT_MATCHING_TYPE;
    }

    return *sokutei_counter_at_index(SOKUTEI_INTEGER_COUNTER_TYPE, index);
}


SOKUTEI_INTEGER_COUNTER_TYPE sokutei_integer_increment_counter(const char *counter_name, const SOKUTEI_INTEGER_COUNTER_TYPE by){
    const int index = sokutei_get_index_of_counter(counter_name);

    if(index == SOKUTEI_NOT_FOUND){
        sokutei_print_error("Counter not found with name: ", counter_name);
        return SOKUTEI_NOT_FOUND;
    }
    if(sokutei_get_type_of(index) != SOKUTEI_INTEGER_TYPE){
        sokutei_print_error("Counter is not of SOKUTEI_INTEGER type: ", counter_name);
        return SOKUTEI_NOT_MATCHING_TYPE;
    }

    return *sokutei_counter_at_index(SOKUTEI_INTEGER_COUNTER_TYPE, index) += by;
}

///--- Integer counter functions
/// Float counter functions

SOKUTEI_FLOAT_COUNTER_TYPE sokutei_float_get_counter(const char *counter_name){
    const int index = sokutei_get_index_of_counter(counter_name);

    if(index == SOKUTEI_NOT_FOUND){
        sokutei_print_error("Counter not found with name: ", counter_name);
        return SOKUTEI_NOT_FOUND;
    }
    if(sokutei_get_type_of(index) != SOKUTEI_FLOAT_TYPE){
        sokutei_print_error("Counter is not of SOKUTEI_FLOAT type: ", counter_name);
        return SOKUTEI_NOT_MATCHING_TYPE;
    }

    return *sokutei_counter_at_index(SOKUTEI_FLOAT_COUNTER_TYPE, index);
}


SOKUTEI_FLOAT_COUNTER_TYPE sokutei_float_increment_counter(const char *counter_name, const SOKUTEI_FLOAT_COUNTER_TYPE by){
    const int index = sokutei_get_index_of_counter(counter_name);

    if(index == SOKUTEI_NOT_FOUND){
        sokutei_print_error("Counter not found with name: ", counter_name);
        return SOKUTEI_NOT_FOUND;
    }

    if(sokutei_get_type_of(index) != SOKUTEI_FLOAT_TYPE){
        sokutei_print_error("Counter is not of SOKUTEI_FLOAT type: ", counter_name);
        return SOKUTEI_NOT_MATCHING_TYPE;
    }
    return *sokutei_counter_at_index(SOKUTEI_FLOAT_COUNTER_TYPE, index) += by;
}

///--- Float counter functions
/// Timer counter functions

SOKUTEI_TIMER_TYPE *sokutei_get_timer_counter(const char *counter_name){
    const int index = sokutei_get_index_of_counter(counter_name);
    if(index == SOKUTEI_NOT_FOUND){
        sokutei_print_error("Counter not found with name: ", counter_name);
        return SOKUTEI_NOT_FOUND;
    }
    if(sokutei_get_type_of(index) != SOKUTEI_INTERVAL_TYPE){
        sokutei_print_error("Counter is not of SOKUTEI_TIMER type: ", counter_name);
        return SOKUTEI_NOT_MATCHING_TYPE;
    }
    return sokutei_counter_at_index(SOKUTEI_TIMER_TYPE, index);
}

void sokutei_timer_to_string(char *buffer, SOKUTEI_TIMER_COUNTER_TYPE *counter){
    // seconds, miliseconds to print??? OS specific
    sokutei_integer_counter_to_string(buffer, counter->elapsed);
}

///--- Timer counter functions

#define SOKUTEI_JSON 0
#define SOKUTEI_CSV 1

#ifndef SOKUTEI_REPORTING_FORMAT
#   define SOKUTEI_REPORTING_FORMAT SOKUTEI_JSON
#endif

#if SOKUTEI_REPORTING_FORMAT == SOKUTEI_JSON
#   define sokutei_begin_report() sokutei_json_begin_report()
#   define sokutei_report_iteration() sokutei_json_report_iteration()
#   define sokutei_end_report() sokutei_json_end_report()
#elif SOKUTEI_REPORTING_FORMAT == SOKUTEI_CSV
#   define sokutei_begin_report() sokutei_csv_begin_report()
#   define sokutei_report_iteration() sokutei_csv_report_iteration()
#   define sokutei_end_report() sokutei_csv_end_report()
#endif

#ifndef sokutei_print_char
#   define sokutei_print_char(char) sokutei_print_char_handler(char)
#endif

#ifndef sokutei_print_string
#   define sokutei_print_string(string) sokutei_print_string_handler(string)
#endif

void sokutei_print_error(const char *error_message, const char *error_param ) {
    sokutei_print_string("SOKUTEI ERROR: [");
    sokutei_print_string(error_message);
    sokutei_print_string(error_param);
    sokutei_print_string("]\n");
}

void sokutei_print_char_handler(const char c) {
}

void sokutei_print_string_handler(const char *string) {
}

void sokutei_convert_counter_to_string(char *target_buffer, const int counter_index) {
    int type_of_counter = sokutei_get_type_of(counter_index);
    if(type_of_counter == SOKUTEI_INTEGER_TYPE) {
        SOKUTEI_INTEGER_COUNTER_TYPE counter_value = *sokutei_counter_at_index(SOKUTEI_INTEGER_COUNTER_TYPE, counter_index);
        sokutei_integer_counter_to_string(target_buffer, counter_value);
    } else if(type_of_counter ==  SOKUTEI_FLOAT_TYPE) {
        SOKUTEI_FLOAT_COUNTER_TYPE counter_value = *sokutei_counter_at_index(SOKUTEI_FLOAT_COUNTER_TYPE, counter_index);
        sokutei_float_counter_to_string(target_buffer, counter_value);
    } else if(type_of_counter == SOKUTEI_INTERVAL_TYPE) {
        SOKUTEI_TIMER_COUNTER_TYPE *counter_value = sokutei_counter_at_index(SOKUTEI_TIMER_COUNTER_TYPE, counter_index);
        sokutei_timer_to_string(target_buffer, counter_value);
    } else {
        sokutei_error_counter_to_string();
    }
}

// json

void sokutei_json_begin_report() {
    sokutei_print_string("[");
}

void sokutei_json_report_iteration(){
    if(sokutei_current_iteration > 0) {
        sokutei_print_string(",");
    }
    sokutei_print_string("{");
    char value_to_string_buffer[SOKUTEI_COUNTER_TO_STRING_BUFFER_LENGTH + 1] = {'\0'};
    int counter;
    for(counter = 0; counter < sokutei_number_of_counters; counter++) {
        if(counter > 0) {
            sokutei_print_string(",");
        }
        sokutei_print_string("\"");
        sokutei_print_string(sokutei_get_counter_name_at_index(counter));
        sokutei_print_string("\":");
        sokutei_convert_counter_to_string(value_to_string_buffer, counter);
        sokutei_print_string(value_to_string_buffer);
    }
    sokutei_print_string("}");
}

void sokutei_json_end_report(){
    sokutei_print_string("]");
}

// csv

void sokutei_csv_begin_report() {
    int counter;
    for(counter = 0; counter < sokutei_number_of_counters; counter++) {
        if(counter > 0) {
            sokutei_print_string(",");
        }
        sokutei_print_string(sokutei_get_counter_name_at_index(counter));
    }
    sokutei_print_string("\n");
}

void sokutei_csv_report_iteration(){
    char value_to_string_buffer[SOKUTEI_COUNTER_TO_STRING_BUFFER_LENGTH + 1] = {'\0'};
    int counter;
    for(counter = 0; counter < sokutei_number_of_counters; counter++) {
        if(counter > 0) {
            sokutei_print_string(",");
        }
        sokutei_convert_counter_to_string(value_to_string_buffer, counter);
        sokutei_print_string(value_to_string_buffer);
    }
    sokutei_print_string("\n");
}

void sokutei_csv_end_report(){
    ;
}




//////------ Iteration handling ------
#define sokutei_iteration_start() ;
#define sokutei_iteration_finish() sokutei_iteration_finish_handler()
//////------ Iteration handling ------//////

////// Counter creations
#define SOKUTEI_DEFINE_COUNTER(counter_name, type) sokutei_add_counter(counter_name, type)
#define sokutei_create_integer_counter(counter_name) SOKUTEI_DEFINE_COUNTER(counter_name, SOKUTEI_INTEGER_TYPE)
#define sokutei_create_float_counter(counter_name) SOKUTEI_DEFINE_COUNTER(counter_name, SOKUTEI_FLOAT_TYPE)
#define sokutei_create_interval_counter(counter_name) SOKUTEI_DEFINE_COUNTER(counter_name, SOKUTEI_INTERVAL_TYPE)
//////------ Counter creations

////// Integer counter operations
#define sokutei_increment_integer_counter(x) sokutei_integer_increment_counter(x, 1)
#define sokutei_alter_integer_counter(x, y) sokutei_integer_increment_counter(x, y)
#define sokutei_get_integer_counter(x) sokutei_integer_get_counter(x)
//////------ Integer counter operations

////// Float counter operations
#define sokutei_increment_float_counter(x) sokutei_float_increment_counter(x, 1.0)
#define sokutei_alter_float_counter(x, y) sokutei_float_increment_counter(x, y)
#define sokutei_get_float_counter(x) sokutei_float_get_counter(x)
//////------ Float counter operations


#define SOKUTEI_COUNT_INTEGER_RETURN_VALUES_AND_REPORT_EVERY_ITERATION_IN_JSON(counter_name, function_name, run_times, function_args...) \
    do {\
        sokutei_create_integer_counter(counter_name);\
        int sokutei_counter;\
        sokutei_iteration_start();\
        sokutei_json_begin_report();\
        for(sokutei_counter = 0; sokutei_counter < run_times; sokutei_counter++){\
            sokutei_integer_increment_counter(counter_name, function_name (function_args));\
            sokutei_json_report_iteration();\
            sokutei_iteration_finish();\
        }\
        sokutei_json_end_report();\
    } while(0);

#define SOKUTEI_COUNT_INTEGER_RETURN_VALUES_AND_REPORT_EVERY_ITERATION_IN_CSV(counter_name, function_name, run_times, ...) \
    do {\
        sokutei_create_integer_counter(counter_name);\
        int sokutei_counter;\
        sokutei_iteration_start();\
        sokutei_csv_begin_report();\
        for(sokutei_counter = 0; sokutei_counter < run_times; sokutei_counter++){\
            sokutei_integer_increment_counter(counter_name, function_name (__VA_ARGS__));\
            sokutei_csv_report_iteration();\
            sokutei_iteration_finish();\
        }\
        sokutei_csv_end_report();\
    } while(0);

#define SOKUTEI_SUM_INTEGER_RETURN_VALUES_IN_JSON(counter_name, function_name, run_times, ...) \
    do {\
        sokutei_create_integer_counter(counter_name);\
        int sokutei_counter;\
        sokutei_iteration_start();\
        sokutei_json_begin_report();\
        for(sokutei_counter = 0; sokutei_counter < run_times; sokutei_counter++){\
            sokutei_integer_increment_counter(counter_name, function_name (__VA_ARGS__));\
        }\
        sokutei_json_report_iteration();\
        sokutei_iteration_finish();\
        sokutei_json_end_report();\
    } while(0);


#define SOKUTEI_SUM_INTEGER_RETURN_VALUES_IN_CSV(counter_name, function_name, run_times, args...) \
    do {\
        sokutei_create_integer_counter(counter_name);\
        int sokutei_counter;\
        sokutei_iteration_start();\
        sokutei_csv_begin_report();\
        for(sokutei_counter = 0; sokutei_counter < run_times; sokutei_counter++){\
            sokutei_integer_increment_counter(counter_name, function_name (__VA_ARGS__));\
        }\
        sokutei_csv_report_iteration();\
        sokutei_iteration_finish();\
        sokutei_csv_end_report();\
    } while(0);


#endif //END OF SOKUTEI_BENCHMARK_H

