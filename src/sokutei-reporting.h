#define SOKUTEI_JSON 0
#define SOKUTEI_CSV 1

#ifndef SOKUTEI_REPORTING_FORMAT
#   define SOKUTEI_REPORTING_FORMAT SOKUTEI_JSON
#endif

#if SOKUTEI_REPORTING_FORMAT == SOKUTEI_JSON
#   define sokutei_begin_report() sokutei_json_begin_report()
#   define sokutei_report_iteration() sokutei_json_report_iteration()
#   define sokutei_end_report() sokutei_json_end_report()
#elif SOKUTEI_REPORTING_FORMAT == SOKUTEI_CSV
#   define sokutei_begin_report() sokutei_csv_begin_report()
#   define sokutei_report_iteration() sokutei_csv_report_iteration()
#   define sokutei_end_report() sokutei_csv_end_report()
#endif

#ifndef sokutei_print_char
#   define sokutei_print_char(char) sokutei_print_char_handler(char)
#endif

#ifndef sokutei_print_string
#   define sokutei_print_string(string) sokutei_print_string_handler(string)
#endif

void sokutei_print_char_handler(const char c) {
}

void sokutei_print_string_handler(const char *string) {
}

void sokutei_convert_counter_to_string(char *target_buffer, const int counter_index) {
    int type_of_counter = sokutei_get_type_of(counter_index);
    if(type_of_counter == SOKUTEI_INTEGER_TYPE) {
        SOKUTEI_INTEGER_COUNTER_TYPE counter_value = *sokutei_counter_at_index(SOKUTEI_INTEGER_COUNTER_TYPE, counter_index);
        sokutei_integer_counter_to_string(target_buffer, counter_value);
    } else if(type_of_counter ==  SOKUTEI_FLOAT_TYPE) {
        SOKUTEI_FLOAT_COUNTER_TYPE counter_value = *sokutei_counter_at_index(SOKUTEI_FLOAT_COUNTER_TYPE, counter_index);
        sokutei_float_counter_to_string(target_buffer, counter_value);
    } else if(type_of_counter == SOKUTEI_INTERVAL_TYPE) {
        SOKUTEI_TIMER_COUNTER_TYPE *counter_value = sokutei_counter_at_index(SOKUTEI_TIMER_COUNTER_TYPE, counter_index);
        sokutei_timer_to_string(target_buffer, counter_value);
    } else {
        sokutei_error_counter_to_string();
    }
}

// json

void sokutei_json_begin_report() {
    sokutei_print_string("[");
}

void sokutei_json_report_iteration(){
    if(sokutei_current_iteration > 0) {
        sokutei_print_string(",");
    }
    sokutei_print_string("{");
    char value_to_string_buffer[SOKUTEI_COUNTER_TO_STRING_BUFFER_LENGTH + 1] = {'\0'};
    int counter;
    for(counter = 0; counter < sokutei_number_of_counters; counter++) {
        if(counter > 0) {
            sokutei_print_string(",");
        }
        sokutei_print_string("\"");
        sokutei_print_string(sokutei_get_counter_name_at_index(counter));
        sokutei_print_string("\":");
        sokutei_convert_counter_to_string(value_to_string_buffer, counter);
        sokutei_print_string(value_to_string_buffer);
    }
    sokutei_print_string("}");
}

void sokutei_json_end_report(){
    sokutei_print_string("]");
}

// csv

void sokutei_csv_begin_report() {
    int counter;
    for(counter = 0; counter < sokutei_number_of_counters; counter++) {
        if(counter > 0) {
            sokutei_print_string(",");
        }
        sokutei_print_string(sokutei_get_counter_name_at_index(counter));
    }
    sokutei_print_string("\n");
}

void sokutei_csv_report_iteration(){
    char value_to_string_buffer[SOKUTEI_COUNTER_TO_STRING_BUFFER_LENGTH + 1] = {'\0'};
    int counter;
    for(counter = 0; counter < sokutei_number_of_counters; counter++) {
        if(counter > 0) {
            sokutei_print_string(",");
        }
        sokutei_convert_counter_to_string(value_to_string_buffer, counter);
        sokutei_print_string(value_to_string_buffer);
    }
    sokutei_print_string("\n");
}

void sokutei_csv_end_report(){
    ;
}

void sokutei_print_error(const char *error_message, const char *error_param ) {
    sokutei_print_string("SOKUTEI ERROR: [");
    sokutei_print_string(error_message);
    sokutei_print_string(error_param);
    sokutei_print_string("]\n");
}
