#ifndef ARITH_DEFINES_H
#define ARITH_DEFINES_H

#include <stdlib.h>

#include "types.h"
#include "log.h"

#ifdef NDEBUG
    #define DEBUG_BREAK()
    #define ASSERT(cond, msg, ...)
#else
    #ifdef __linux__
        #define DEBUG_BREAK() __builtin_trap()
    #elif _WIN32
        #define DEBUG_BREAK() __debugbreak()
    #endif

    #define ARITH_ASSERT(cond, msg, ...)               \
    {                                                  \
        if(!(cond))                                    \
        {                                              \
            ARITH_LOG(LOG_ERROR, msg, ##__VA_ARGS__);  \
            DEBUG_BREAK();                             \
        }                                              \
    }
#endif

#define ALIGNED_SIZE(size, alignment) ((size) % (alignment) == 0) ? (size) : (size) + ((alignment) - ((size) % (alignment)))

#define CLAMP(val, lower, upper) ((val) < (lower)) ? (lower) : ((val) > (upper)) ? (upper) : (val)

#endif