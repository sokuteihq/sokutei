
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
