
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


int sokutei_integer_counter_to_string(char *target_buffer, SOKUTEI_INTEGER_COUNTER_TYPE integer){
    char local_buffer[SOKUTEI_COUNTER_TO_STRING_BUFFER_LENGTH + 1] = {'\0'};
    int index = SOKUTEI_COUNTER_TO_STRING_BUFFER_LENGTH;
    int length = 0;
    if(integer < 0){
        target_buffer[0] = '-';
        length = 1;
        integer *= -1;
    }

    do{
        local_buffer[index--] = '0' + (integer % 10);
        integer /= 10;
    } while(integer);

    index++;

    while(index <= SOKUTEI_COUNTER_TO_STRING_BUFFER_LENGTH){
        target_buffer[length++] = local_buffer[index++];
    }
    return length;
}


int sokutei_float_counter_to_string(char *target_buffer, SOKUTEI_FLOAT_COUNTER_TYPE floating_point){
    int digits = 0;
    SOKUTEI_INTEGER_COUNTER_TYPE integer_part = floating_point;
    floating_point -= integer_part;
    digits = sokutei_integer_counter_to_string(target_buffer, integer_part);

    target_buffer[digits++] = '.';
    int precision;
    for (precision = 0; precision < SOKUTEI_COUNTER_TO_STRING_PRECISION - 1; precision++){
        floating_point *= 10;
        integer_part = (SOKUTEI_INTEGER_COUNTER_TYPE) floating_point;
        floating_point -= integer_part;
        digits += sokutei_integer_counter_to_string(target_buffer + digits, integer_part) ;
    }
    integer_part = floating_point *= 10;

    return digits;
}


void sokutei_error_counter_to_string(){
}
