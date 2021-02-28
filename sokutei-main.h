#ifndef SOKUTEI_BENCHMARK_H
#define SOKUTEI_BENCHMARK_H

/// Determine operating system
#ifndef SOKUTEI_OS_TYPE

#define SOKUTEI_LINUX 1
#define SOKUTEI_WINDOWS 2
#define SOKUTEI_MACOS 3
#define SOKUTEI_ARDUINO 4

#if defined(linux) || defined(_linux) || defined(__linux__) || defined(__unix__) // Linux
#   define SOKUTEI_OS_TYPE SOKUTEI_LINUX
#elif defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS) || defined(__WINDOWS__) // Windows
#   define SOKUTEI_OS_TYPE SOKUTEI_WINDOWS
#elif (defined(__MACH__) && defined(__APPLE__)) // MacOs
#   define SOKUTEI_OS_TYPE SOKUTEI_MACOS
#elif defined(ARDUINO) // Arduino
#   define SOKUTEI_OS_TYPE SOKUTEI_ARDUINO
#endif

#include "./platforms/sokutei-common.h"

#include "./platforms/sokutei-cuda.h"
#include "./platforms/sokutei-windows.h"
#include "./platforms/sokutei-linux.h"
#include "./platforms/sokutei-macos.h"
#include "./platforms/sokutei-arduino.h"



#ifndef SOKUTEI_TIMER_COUNTER_TYPE
#   define SOKUTEI_TIMER_COUNTER_TYPE SOKUTEI_TIMER_TYPE
#endif

#ifndef SOKUTEI_TIMER_START
#   define SOKUTEI_TIMER_START sokutei_timer_start_function
#endif

#ifndef SOKUTEI_TIMER_STOP
#   define SOKUTEI_TIMER_STOP sokutei_timer_stop_function
#endif

#endif
///--- Determine operating system

#define SOKUTEI_MAX_COUNTER_COUNT  100
#define SOKUTEI_MAX_COUNTER_NAME_LENGTH 30

#define SOKUTEI_COUNTER_TO_STRING_BUFFER_LENGTH 64
#define SOKUTEI_COUNTER_TO_STRING_PRECISION 15

#define SOKUTEI_INTEGER_COUNTER_TYPE int
#define SOKUTEI_FLOAT_COUNTER_TYPE double


#define MAX_SIZE_OF_TYPES   ((sizeof(SOKUTEI_INTEGER_COUNTER_TYPE) > sizeof(SOKUTEI_FLOAT_COUNTER_TYPE)) \
                            ? ((sizeof(SOKUTEI_INTEGER_COUNTER_TYPE) > sizeof(SOKUTEI_TIMER_COUNTER_TYPE)) \
                                ? sizeof(SOKUTEI_INTEGER_COUNTER_TYPE) \
                                : sizeof(SOKUTEI_TIMER_COUNTER_TYPE))\
                            : ((sizeof(SOKUTEI_FLOAT_COUNTER_TYPE) > sizeof(SOKUTEI_TIMER_COUNTER_TYPE)) \
                                ? sizeof(SOKUTEI_FLOAT_COUNTER_TYPE) \
                                : sizeof(SOKUTEI_TIMER_COUNTER_TYPE)))

#define SOKUTEI_INTEGER_TYPE '1'
#define SOKUTEI_FLOAT_TYPE '2'
#define SOKUTEI_INTERVAL_TYPE '3'

#define SOKUTEI_NOT_FOUND -1
#define SOKUTEI_NOT_MATCHING_TYPE -2
#define SOKUTEI_COUNTER_LIMIT_REACHED -3
#define SOKUTEI_COUNTER_ALREADY_EXISTS -4

/**
 * Padding sets the number of bytes to separate names from type indicators, do we need to separate the type indicator with its own string terminator?
 */
#define SOKUTEI_TYPE_INDICATOR_PADDING 2

/**
 * SOKUTEI_TYPE_INDICATOR_INDEX is the index of the type indicator, which is positioned after the counter name's maximal index.
 */
#define SOKUTEI_TYPE_INDICATOR_INDEX (SOKUTEI_MAX_COUNTER_NAME_LENGTH + 1)


#ifdef SOKUTEI_LOGGING_ENABLED
#define SOKUTEI_DEBUG_PRINT(x, y) printf(x, y)
#else
#define SOKUTEI_DEBUG_PRINT(x, y)
#endif



/// String functions
#include "src/sokutei-string-functions.h"
///--- String functions


/// Counters
#include "src/sokutei-counters.h"
///--- Counters



/// Iterations

int sokutei_current_iteration = 0;


void sokutei_iteration_finish_handler(){
    int index;
    for(index = 0; index < (SOKUTEI_MAX_COUNTER_COUNT * MAX_SIZE_OF_TYPES); index++){
        sokutei_counters[index] = 0;
    }
    sokutei_current_iteration++;
}

///--- Iterations

#include "src/sokutei-counter-handling.h"
#include "src/sokutei-reporting.h"
#include "src/sokutei-api.h"
#include "src/sokutei-templates.h"

#endif //END OF SOKUTEI_BENCHMARK_H
