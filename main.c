#include <stdio.h>
#define SOKUTEI_NO_STDLIB
#include "sokutei.h"

void iterate2(int i){
    sokutei_iteration_start();
    int a = 0;
    sokutei_create_integer_counter("ITER");
    sokutei_create_float_counter("FLOAT");
    for(a = 0; a < i; a++){
        sokutei_alter_integer_counter("ITER", 1);
        sokutei_alter_float_counter("FLOAT", 1);
    }
    sokutei_iteration_finish();
}
void iterate(int i) {
    sokutei_create_integer_counter("ITER");

    int a = 0;
    for (a = 0; a < i; a++) {
        sokutei_iteration_start();
        sokutei_alter_integer_counter("ITER", a);
        printf("ITER: %d\n", sokutei_get_integer_counter("ITER"));
        sokutei_iteration_finish();
    }

}

int main() {
    printf("%d\n", MAX_SIZE_OF_TYPES);
    iterate(10);
    printf("%d\n", sokutei_get_integer_counter("ITER"));
    //printf("%f\n", SOKUTEI_GET_FLOAT_COUNTER("FLOAT"));
    return 0;
}
