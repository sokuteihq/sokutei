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
