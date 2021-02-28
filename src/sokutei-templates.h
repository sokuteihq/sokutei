
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
