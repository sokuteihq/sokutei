#ifndef SOKUTEI_BENCHMARK_H
#define SOKUTEI_BENCHMARK_H

#define SOKUTEI_ITERATIONS 10
#define SOKUTEI_MAX_COUNTER_COUNT  100
#define SOKUTEI_COUNTER_LENGTH 30
#define SOKUTEI_INTEGER_COUNTER_TYPE int
#define SOKUTEI_FLOAT_COUNTER_TYPE double
#define SOKUTEI_INTERVAL_TIMER_COUNTER_TYPE int

#define MAX_SIZE_OF_TYPES   sizeof(SOKUTEI_INTEGER_COUNTER_TYPE) > sizeof(SOKUTEI_FLOAT_COUNTER_TYPE) \
                            ? sizeof(SOKUTEI_INTEGER_COUNTER_TYPE) > sizeof(SOKUTEI_INTERVAL_TIMER_COUNTER_TYPE) \
                                ? sizeof(SOKUTEI_INTEGER_COUNTER_TYPE) \
                                : sizeof(SOKUTEI_INTERVAL_TIMER_COUNTER_TYPE)\
                            : sizeof(SOKUTEI_FLOAT_COUNTER_TYPE) > sizeof(SOKUTEI_INTERVAL_TIMER_COUNTER_TYPE) \
                                ? sizeof(SOKUTEI_FLOAT_COUNTER_TYPE) \
                                : sizeof(SOKUTEI_INTERVAL_TIMER_COUNTER_TYPE)

#define SOKUTEI_INTEGER_TYPE '1'
#define SOKUTEI_FLOAT_TYPE '2'
#define SOKUTEI_INTERVAL_TYPE '3'

#define NOT_FOUND -1
#define NOT_MATCHING_TYPE -2


int sokutei_strcmp(const char *string_a, const char *string_b){
    int i = 0;
    while(string_a[i] == string_b[i] && string_a[i]) i++;
    return string_a[i] - string_b[i];
}
#define STRCMP(string_a, string_b) sokutei_strcmp(string_a, string_b)

char *sokutei_strcpy(char *string_a, const char *string_b){
    int i;
    for(i = 0; (string_a[i] = string_b[i]) && (i < SOKUTEI_COUNTER_LENGTH); i++);
    string_a[SOKUTEI_COUNTER_LENGTH] = '\0';
    return string_a;
}
#define STRCPY(string_a, string_b) sokutei_strcpy(string_a, string_b)
#define string_equals(string_a, string_b) (STRCMP(string_a, string_b) == 0)






char sokutei_counter_names[SOKUTEI_MAX_COUNTER_COUNT][SOKUTEI_COUNTER_LENGTH + 2] = {'\0'};
char sokutei_counters[SOKUTEI_MAX_COUNTER_COUNT * MAX_SIZE_OF_TYPES] = {0};
int  sokutei_number_of_counters = 0; //this buddy gets overwritten when positioned at 40. line



char sokutei_get_type_of(int index){
    return sokutei_counter_names[index][31];
}


int sokutei_get_index_of_counter(const char *counter_name){
    int i;
    printf("number of sokutei counters: %d\n", sokutei_number_of_counters);
    for(i = 0; i < sokutei_number_of_counters; i++){
        printf("|%s| |%s|", counter_name, sokutei_counter_names[i]);
        if(string_equals(sokutei_counter_names[i], counter_name)){
            return i;
        }
    }
    return NOT_FOUND;
}


void sokutei_add_counter(const char *counter_name, char type){

    if(type != SOKUTEI_INTEGER_TYPE && type != SOKUTEI_FLOAT_TYPE && type != SOKUTEI_INTERVAL_TYPE){
        return;
    }
    STRCPY(sokutei_counter_names[sokutei_number_of_counters], counter_name);
    sokutei_counter_names[sokutei_number_of_counters][SOKUTEI_COUNTER_LENGTH + 1] = type;
    printf("%s\n", sokutei_counter_names[sokutei_number_of_counters]);
    sokutei_number_of_counters++;
}


SOKUTEI_INTEGER_COUNTER_TYPE sokutei_integer_get_counter(const char *counter_name){
    int index = sokutei_get_index_of_counter(counter_name);

    if(index == NOT_FOUND){
        return NOT_FOUND;
    }
    if(sokutei_get_type_of(index) != SOKUTEI_INTEGER_TYPE){
        fprintf(stderr, "NOT MATCHING TYPE!\n");
        return NOT_MATCHING_TYPE;
    }
    SOKUTEI_INTEGER_COUNTER_TYPE *counter = sokutei_counters + (index * MAX_SIZE_OF_TYPES);

    if(&sokutei_number_of_counters == counter){
        printf("BAJ VAN!");
    }

    return *counter;
}


SOKUTEI_INTEGER_COUNTER_TYPE //:)
sokutei_integer_increment_counter(const char *counter_name, SOKUTEI_INTEGER_COUNTER_TYPE by){
    int index = sokutei_get_index_of_counter(counter_name);

    printf("\nindex = %d\n", index);
    printf("MAX_SIZE_OF_TYPES = %llu\n", MAX_SIZE_OF_TYPES);
    printf("index * MAX_SIZE_OF_TYPES = %llu\n", index * (int)MAX_SIZE_OF_TYPES);
    if(index == NOT_FOUND){
        return NOT_FOUND;
    }
    if(sokutei_get_type_of(index) != SOKUTEI_INTEGER_TYPE){
        fprintf(stderr, "NOT MATCHING TYPE!\n");
        return NOT_MATCHING_TYPE;
    }
    SOKUTEI_INTEGER_COUNTER_TYPE *counter = (void *)sokutei_counters + (index * MAX_SIZE_OF_TYPES);
    printf("MERETE::||%d||\n", (void *)counter - (void *)sokutei_counters);
    if(&sokutei_number_of_counters == counter){
        printf("BAJ VAN!!");
    }
    return *counter += by;
}



SOKUTEI_FLOAT_COUNTER_TYPE sokutei_float_get_counter(const char *counter_name){
    int index = sokutei_get_index_of_counter(counter_name);

    if(index == NOT_FOUND){
        return NOT_FOUND;
    }
    if(sokutei_get_type_of(index) != SOKUTEI_FLOAT_TYPE){
        fprintf(stderr, "NOT MATCHING TYPE!\n");
        return NOT_MATCHING_TYPE;
    }

    SOKUTEI_FLOAT_COUNTER_TYPE *counter = sokutei_counters + (index * MAX_SIZE_OF_TYPES);
    if(&sokutei_number_of_counters == counter){
        printf("BAJ VAN!!!");
    }
    return (SOKUTEI_FLOAT_COUNTER_TYPE) *counter;
}


SOKUTEI_FLOAT_COUNTER_TYPE sokutei_float_increment_counter(const char *counter_name, SOKUTEI_FLOAT_COUNTER_TYPE by){
    int index = sokutei_get_index_of_counter(counter_name);

    printf("%d\n", index);
    if(index == NOT_FOUND){
        return NOT_FOUND;
    }

    if(sokutei_get_type_of(index) != SOKUTEI_FLOAT_TYPE){
        fprintf(stderr, "NOT MATCHING TYPE!\n");
        return NOT_MATCHING_TYPE;
    }

    SOKUTEI_FLOAT_COUNTER_TYPE *counter = sokutei_counters + (index * MAX_SIZE_OF_TYPES);
    printf("MERETE::||%d||\n", (void *)counter - (void *)sokutei_counters);

    if(&sokutei_number_of_counters == counter){
        printf("BAJ VAN!!!!");
    }
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