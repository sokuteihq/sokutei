
#define sokutei_print_char(char) print_char(char)
#define sokutei_print_string(string) printf("%s", string);

#include "../../../greatest.h"
#include "../../../sokutei.h"

int dummy(int i){
    return i;
}

int main(){
    SOKUTEI_COUNT_INTEGER_RETURN_VALUES_AND_REPORT_EVERY_ITERATION_JSON("asda", dummy, 5, 5);
    return 0;
}
