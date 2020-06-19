#include <stdio.h>
#define SOKUTEI_NO_STDLIB
#include "sokutei.h"

void iterate(int i){
    int a = 0;
    SOKUTEI_DEFINE_COUNTER("ITER");
    for(a = 0; a < i; a++){
        SOKUTEI_INCREMENT_COUNTER("ITER");
    }
}

int main() {
    iterate(10);
    printf("%d\n", SOKUTEI_GET_COUNTER("ITER"));
    return 0;
}
