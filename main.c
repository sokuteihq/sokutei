#include <stdio.h>
#define SOKUTEI_NO_STDLIB
#include "sokutei.h"

void iterate(int i){
    int a = 0;
    sokutei_create_integer_counter("ITER");
    sokutei_create_float_counter("FLOAT");
    for(a = 0; a < i; a++){
        sokutei_alter_integer_counter("FLOAT", 1);
        sokutei_alter_float_counter("FLOAT", 1);
    }
}

int main() {
    printf("%d\n", MAX_SIZE_OF_TYPES);
    iterate(10);
    printf("%d\n", sokutei_get_integer_counter("ITER"));
    //printf("%f\n", SOKUTEI_GET_FLOAT_COUNTER("FLOAT"));
    return 0;
}
