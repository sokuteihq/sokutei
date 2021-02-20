
/// Integer counter functions
SOKUTEI_INTEGER_COUNTER_TYPE sokutei_integer_get_counter(const char *counter_name){
    const int index = sokutei_get_index_of_counter(counter_name);

    if(index == SOKUTEI_NOT_FOUND){
        return SOKUTEI_NOT_FOUND;
    }
    if(sokutei_get_type_of(index) != SOKUTEI_INTEGER_TYPE){
        //TODO call error
        /*
         * print error to output, and stop any printing after?
         */
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

///--- Integer counter functions
/// Float counter functions

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

///--- Float counter functions
/// Timer counter functions

SOKUTEI_TIMER_TYPE *sokutei_get_timer_counter(const char *counter_name){
    const int index = sokutei_get_index_of_counter(counter_name);
    if(index == SOKUTEI_NOT_FOUND){
        return SOKUTEI_NOT_FOUND;
    }
    if(sokutei_get_type_of(index) != SOKUTEI_INTERVAL_TYPE){
        //TODO call error
        return SOKUTEI_NOT_MATCHING_TYPE;
    }
    return sokutei_counter_at_index(SOKUTEI_TIMER_TYPE, index);
}

void sokutei_timer_to_string(char *buffer, SOKUTEI_TIMER_COUNTER_TYPE *counter){
    // seconds, miliseconds to print??? OS specific
    sokutei_integer_counter_to_string(buffer, counter->elapsed);
}

///--- Timer counter functions
