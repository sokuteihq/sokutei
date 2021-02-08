#ifndef SOKUTEI_SOKUTEI_CUDA_H
#define SOKUTEI_SOKUTEI_CUDA_H

#if SOKUTEI_OS_TYPE == SOKUTEI_CUDA

    typedef struct couter_type{
        cudaEvent_t start;
        cudaEvent_t stop;
        unsigned int elapsed;
    } SOKUTEI_TIMER_TYPE;


    SOKUTEI_TIMER_TYPE *sokutei_get_timer_counter(const char *);

    void sokutei_timer_start_function(char *counter_name){
        SOKUTEI_TIMER_TYPE *counter = sokutei_get_timer_counter(counter_name);
        cudaEventCreate(&(counter->start));
        cudaEventCreate(&(counter->stop));
        cudaEventRecord(counter->start);
    }

    void sokutei_timer_start_function(char *counter_name){
        SOKUTEI_TIMER_TYPE *counter = sokutei_get_timer_counter(counter_name);
        cudaEventRecord(counter->stop);
        cudaEventSynchronize(counter->stop);
        cudaEventElapsedTime(&(counter->elapsed), counter->start, counter->stop);
    }

#   ifndef SOKUTEI_CUSTOM_TIMER
#   endif //SOKUTEI_CUSTOM_TIMER
#endif //CONDITIONAL
#endif //SOKUTEI_SOKUTEI_CUDA_H
