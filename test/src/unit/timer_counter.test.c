#include <stdio.h>

char buffer[1024] = {'\0'};
int number_of_chars = 0;

void print_char(const char c){
    buffer[number_of_chars++] = c;
    buffer[number_of_chars] = '\0';
}

void print_string(const char *string) {
    int index = 0;
    while(string[index]) {
        print_char(string[index++]);
    }
}

#define sokutei_print_char(char) putchar(char)
#define sokutei_print_string(string) printf("%s", string)

#define SOKUTEI_REPORTING_FORMAT 0
#include "../../sokutei.h"

int a(int n){
    if(n == 0){
        return 0;
    }
    return a(n - 1);
}

int main(){
    printf("HENLOOO\n");
    sokutei_create_interval_counter("asdaq");

    sokutei_begin_report();
    sokutei_report_iteration();
    sokutei_iteration_finish();

    SOKUTEI_TIMER_START("asdaq");

    int i;
    for(i = 1; i < 33000; i++){
        a(i);
    }
    SOKUTEI_TIMER_STOP("asdaq");

    sokutei_report_iteration();
    sokutei_end_report();
    printf("HENLOOO\n");
    return 0;
}