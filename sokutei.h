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

///--- String functions


/// Counters

/**
 * sokutei_counter_definitions is an array, which consists of the counter name followed by string terminator (\0), and the type of the counter.
 */
char sokutei_counter_definitions[SOKUTEI_MAX_COUNTER_COUNT][SOKUTEI_MAX_COUNTER_NAME_LENGTH + SOKUTEI_TYPE_INDICATOR_PADDING] = {'\0'};


char sokutei_counters[SOKUTEI_MAX_COUNTER_COUNT * MAX_SIZE_OF_TYPES] = {0};
int sokutei_number_of_counters = 0;

///--- Counters


/// Low level counter handling

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
    return sokutei_number_of_counters + 1 >= SOKUTEI_MAX_COUNTER_COUNT;
}


inline int sokutei_create_new_counter(const char *counter_name, const char type){
    sokutei_strcpy(sokutei_counter_definitions[sokutei_number_of_counters], counter_name);
    sokutei_counter_definitions[sokutei_number_of_counters][SOKUTEI_TYPE_INDICATOR_INDEX] = type;
    sokutei_number_of_counters++;
    return 0;
}


int sokutei_add_counter(const char *counter_name, const char type){
    if(sokutei_is_unknown_counter_type(type)){
        return SOKUTEI_NOT_MATCHING_TYPE;
    }

    if(sokutei_is_counter_limit_reached()){
        return SOKUTEI_COUNTER_LIMIT_REACHED;
    }

    if(sokutei_get_index_of_counter(counter_name) != SOKUTEI_NOT_FOUND){
        return SOKUTEI_COUNTER_ALREADY_EXISTS;
    }

    return sokutei_create_new_counter(counter_name, type);
}

///--- Low level counter handling


/// Iterations

int sokutei_number_of_iterations =
        SOKUTEI_MAX_MEASURED_ITERATIONS;

int sokutei_current_iteration = 0;


void sokutei_iteration_finish_handler(){
    int index;
    for(index = 0; index < (SOKUTEI_MAX_COUNTER_COUNT * MAX_SIZE_OF_TYPES); index++){
        sokutei_counters[index] = 0;
    }
}

///--- Iterations


/// Counter Getter and Setter functions

SOKUTEI_INTEGER_COUNTER_TYPE sokutei_integer_get_counter(const char *counter_name){
    const int index = sokutei_get_index_of_counter(counter_name);

    if(index == SOKUTEI_NOT_FOUND){
        return SOKUTEI_NOT_FOUND;
    }
    if(sokutei_get_type_of(index) != SOKUTEI_INTEGER_TYPE){
        //TODO call error
        return SOKUTEI_NOT_MATCHING_TYPE;
    }

    return *sokutei_counter_at_index(SOKUTEI_INTEGER_COUNTER_TYPE, index);
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

    return *sokutei_counter_at_index(SOKUTEI_INTEGER_COUNTER_TYPE, index) += by;
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

    return *sokutei_counter_at_index(SOKUTEI_FLOAT_COUNTER_TYPE, index);
}


SOKUTEI_FLOAT_COUNTER_TYPE sokutei_float_increment_counter(const char *counter_name, const SOKUTEI_FLOAT_COUNTER_TYPE by){
    const int index = sokutei_get_index_of_counter(counter_name);

    if(index == SOKUTEI_NOT_FOUND){
        return SOKUTEI_NOT_FOUND;
    }

    if(sokutei_get_type_of(index) != SOKUTEI_FLOAT_TYPE){
        // TODO call error
        return SOKUTEI_NOT_MATCHING_TYPE;
    }
    
    return *sokutei_counter_at_index(SOKUTEI_FLOAT_COUNTER_TYPE, index) += by;
}

///--- Counter Getter and Setter functions








///------------ Sokutei API ----

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

///--- Sokutei API


#endif //END OF SOKUTEI_BENCHMARK_H

