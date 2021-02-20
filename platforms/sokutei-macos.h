#if SOKUTEI_OS_TYPE == SOKUTEI_MACOS

#ifndef SOKUTEI_SOKUTEI_PLATFORM_H
#define SOKUTEI_SOKUTEI_PLATFORM_H

#   include <stdio.h>

#   ifndef sokutei_print_string
#       define sokutei_print_string(string) printf("%s", string);
#   endif


#   ifndef SOKUTEI_CUSTOM_TIMER
#   endif //SOKUTEI_CUSTOM_TIMER
#endif //CONDITIONAL
#endif //SOKUTEI_SOKUTEI_PLATFORM_H
