#ifndef SOKUTEI_BENCHMARK
#define SOKUTEI_BENCHMARK

#define MAX_COUNTERS 100
#define COUNTER_LENGTH 32
#define INT int

#ifdef SOKUTEI_NO_STDLIB
#ifndef SOKUTEI_STDLIB
#define SOKUTEI_STDLIB

int sokutei_strcmp(const char *a, const char *b){
    int i = 0;
    while(a[i] && b[i] && a[i] == b[i]) i++;
    return a[i] - b[i];
}
#define STRCMP(a, b) sokutei_strcmp(a, b)

char *sokutei_strcpy(char *a, const char *b){
    int i;
    for(i = 0; a[i] = b[i]; i++);
    return a;
}
#define STRCPY(a, b) sokutei_strcpy(a, b)

#endif //END OF SOKUTEI_STDLIB
#else
#include <string.h>
#include <stdio.h>
#define STRCMP(a, b) strcmp(a, b)
#define STRCPY(a, b) strcpy(a, b)

#endif //END OF SOKUTEI_NO_STDLIB

char sokutei_int_counter_names[MAX_COUNTERS][COUNTER_LENGTH] = {'\0'};
INT  sokutei_int_counters[MAX_COUNTERS] = {0};
int  sokutei_int_number_of_counters = 0;

void sokutei_add_counter(const char *ctr){
    STRCPY(sokutei_int_counter_names[sokutei_int_number_of_counters++], ctr);
}

int sokutei_int_increment_counter(const char *ctr, int by){
    int i;
    for(i = 0; i < sokutei_int_number_of_counters; i++){
        if(STRCMP(sokutei_int_counter_names[i], ctr) == 0){
            break;
        }
    }
    if(i == sokutei_int_number_of_counters){
        return -1;
    }
    return sokutei_int_counters[i] += by;
}

int sokutei_int_get_counter(const char *ctr){
    int i;
    for(i = 0; i < sokutei_int_number_of_counters; i++){
        if(STRCMP(sokutei_int_counter_names[i], ctr) == 0){
            return sokutei_int_counters[i];
        }
    }
    return -1;
}

#define SOKUTEI_DEFINE_COUNTER(x) sokutei_add_counter(x)
#define SOKUTEI_INCREMENT_COUNTER(x) sokutei_int_increment_counter(x, 1)
#define SOKUTEI_INCREMENT_COUNTER_BY(x, y) sokutei_int_increment_counter(x, y)
#define SOKUTEI_GET_COUNTER(x) sokutei_int_get_counter(x)


#endif //END OF SOKUTEI_BENCHMARK