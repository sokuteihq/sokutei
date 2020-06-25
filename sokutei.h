#ifndef SOKUTEI_BENCHMARK_H
#define SOKUTEI_BENCHMARK_H

#define SOKUTEI_MAX_MEASURED_ITERATIONS 10
#define SOKUTEI_MAX_COUNTER_COUNT  100
#define SOKUTEI_MAX_COUNTER_NAME_LENGTH 30
#define SOKUTEI_INTEGER_COUNTER_TYPE int
#define SOKUTEI_FLOAT_COUNTER_TYPE double
#define SOKUTEI_INTERVAL_TIMER_COUNTER_TYPE int

#define MAX_SIZE_OF_TYPES   ((sizeof(SOKUTEI_INTEGER_COUNTER_TYPE) > sizeof(SOKUTEI_FLOAT_COUNTER_TYPE)) \
                            ? ((sizeof(SOKUTEI_INTEGER_COUNTER_TYPE) > sizeof(SOKUTEI_INTERVAL_TIMER_COUNTER_TYPE)) \
                                ? sizeof(SOKUTEI_INTEGER_COUNTER_TYPE) \
                                : sizeof(SOKUTEI_INTERVAL_TIMER_COUNTER_TYPE))\
                            : ((sizeof(SOKUTEI_FLOAT_COUNTER_TYPE) > sizeof(SOKUTEI_INTERVAL_TIMER_COUNTER_TYPE)) \
                                ? sizeof(SOKUTEI_FLOAT_COUNTER_TYPE) \
                                : sizeof(SOKUTEI_INTERVAL_TIMER_COUNTER_TYPE)))

#define SOKUTEI_INTEGER_TYPE '1'
#define SOKUTEI_FLOAT_TYPE '2'
#define SOKUTEI_INTERVAL_TYPE '3'

#define SOKUTEI_NOT_FOUND -1
#define SOKUTEI_NOT_MATCHING_TYPE -2
#define SOKUTEI_COUNTER_LIMIT_REACHED -3


#ifdef SOKUTEI_LOGGING_ENABLED
#define SOKUTEI_DEBUG_PRINT(x, y) printf(x, y)
#else
#define SOKUTEI_DEBUG_PRINT(x, y)
#endif


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


int sokutei_number_of_iterations = SOKUTEI_MAX_MEASURED_ITERATIONS;

/**
 * sokutei_counter_definitions is an array consist of the counter name followed by string separator (\0), and the type of the counter
 */
char sokutei_counter_definitions[SOKUTEI_MAX_COUNTER_COUNT][SOKUTEI_MAX_COUNTER_NAME_LENGTH + 2] = {'\0'};


char sokutei_counters[SOKUTEI_MAX_COUNTER_COUNT * MAX_SIZE_OF_TYPES * SOKUTEI_MAX_MEASURED_ITERATIONS] = {0};
int  sokutei_number_of_counters = 0;
int number_of_iterations = SOKUTEI_MAX_MEASURED_ITERATIONS;


char sokutei_get_type_of(const int index){
    return sokutei_counter_definitions[index][31];
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


void sokutei_set_number_of_iterations(const int iterations){

    if(SOKUTEI_MAX_MEASURED_ITERATIONS < iterations){
        //TODO call error
        return;
    }

    number_of_iterations = iterations;
}


int sokutei_add_counter(const char *counter_name, char type){

    if(type != SOKUTEI_INTEGER_TYPE && type != SOKUTEI_FLOAT_TYPE && type != SOKUTEI_INTERVAL_TYPE){
        return SOKUTEI_NOT_MATCHING_TYPE;
    }

    if(sokutei_number_of_counters + 1 >= SOKUTEI_MAX_COUNTER_COUNT){
        return SOKUTEI_COUNTER_LIMIT_REACHED;
    }

    sokutei_strcpy(sokutei_counter_definitions[sokutei_number_of_counters], counter_name);
    sokutei_counter_definitions[sokutei_number_of_counters][SOKUTEI_MAX_COUNTER_NAME_LENGTH + 1] = type;
    sokutei_number_of_counters++;
}


SOKUTEI_INTEGER_COUNTER_TYPE sokutei_integer_get_counter(const char *counter_name){
    const int index = sokutei_get_index_of_counter(counter_name);

    if(index == SOKUTEI_NOT_FOUND){
        return SOKUTEI_NOT_FOUND;
    }
    if(sokutei_get_type_of(index) != SOKUTEI_INTEGER_TYPE){
        //TODO call error
        return SOKUTEI_NOT_MATCHING_TYPE;
    }

    SOKUTEI_INTEGER_COUNTER_TYPE *counter = sokutei_counters + (index * MAX_SIZE_OF_TYPES);

    return *counter;
}


SOKUTEI_INTEGER_COUNTER_TYPE sokutei_integer_increment_counter(const char *counter_name, const SOKUTEI_INTEGER_COUNTER_TYPE by){
    const int index = sokutei_get_index_of_counter(counter_name);

    if(index == SOKUTEI_NOT_FOUND){
        return SOKUTEI_NOT_FOUND;
    }
    if(sokutei_get_type_of(index) != SOKUTEI_INTEGER_TYPE){
        //TODO call error
        return SOKUTEI_NOT_MATCHING_TYPE;
    }

    SOKUTEI_INTEGER_COUNTER_TYPE *counter = (void *)sokutei_counters + (index * MAX_SIZE_OF_TYPES);

    return *counter += by;
}


SOKUTEI_FLOAT_COUNTER_TYPE sokutei_float_get_counter(const char *counter_name){
    const int index = sokutei_get_index_of_counter(counter_name);

    if(index == SOKUTEI_NOT_FOUND){
        return SOKUTEI_NOT_FOUND;
    }
    if(sokutei_get_type_of(index) != SOKUTEI_FLOAT_TYPE){
        //TODO call error
        return SOKUTEI_NOT_MATCHING_TYPE;
    }

    SOKUTEI_FLOAT_COUNTER_TYPE *counter = sokutei_counters + (index * MAX_SIZE_OF_TYPES);

    return (SOKUTEI_FLOAT_COUNTER_TYPE) *counter;
}


SOKUTEI_FLOAT_COUNTER_TYPE sokutei_float_increment_counter(const char *counter_name, SOKUTEI_FLOAT_COUNTER_TYPE by){
    const int index = sokutei_get_index_of_counter(counter_name);

    if(index == SOKUTEI_NOT_FOUND){
        return SOKUTEI_NOT_FOUND;
    }

    if(sokutei_get_type_of(index) != SOKUTEI_FLOAT_TYPE){
        //TODO call error
        return SOKUTEI_NOT_MATCHING_TYPE;
    }

    SOKUTEI_FLOAT_COUNTER_TYPE *counter = sokutei_counters + (index * MAX_SIZE_OF_TYPES);

    return *counter += by;
}


/// Counter creations
#define SOKUTEI_DEFINE_COUNTER(counter_name, type) sokutei_add_counter(counter_name, type)
#define sokutei_create_integer_counter(counter_name) SOKUTEI_DEFINE_COUNTER(counter_name, SOKUTEI_INTEGER_TYPE)
#define sokutei_create_float_counter(counter_name) SOKUTEI_DEFINE_COUNTER(counter_name, SOKUTEI_FLOAT_TYPE)
#define sokutei_create_interval_counter(counter_name) SOKUTEI_DEFINE_COUNTER(counter_name, SOKUTEI_INTERVAL_TYPE)


/// Integer counter operations
//#define SOKUTEI_INCREMENT_INTEGER_COUNTER(x) sokutei_integer_increment_counter(x, 1)
#define sokutei_alter_integer_counter(x, y) sokutei_integer_increment_counter(x, y)
#define sokutei_get_integer_counter(x) sokutei_integer_get_counter(x)

//#define sokutei_alter_float_counter(x) sokutei_float_increment_counter(x, 1.0)
#define sokutei_alter_float_counter(x, y) sokutei_float_increment_counter(x, y)
#define sokutei_get_float_counter(x) sokutei_float_get_counter(x)



#endif //END OF SOKUTEI_BENCHMARK_H