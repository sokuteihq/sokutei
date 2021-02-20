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
