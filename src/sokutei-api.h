
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
