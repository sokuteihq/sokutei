#if SOKUTEI_OS_TYPE == SOKUTEI_LINUX

#ifndef SOKUTEI_SOKUTEI_LINUX_H
#define SOKUTEI_SOKUTEI_LINUX_H

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
#endif //SOKUTEI_SOKUTEI_LINUX_H
