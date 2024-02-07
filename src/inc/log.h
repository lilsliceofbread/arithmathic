#ifndef ARITH_LOG_H
#define ARITH_LOG_H

#include "types.h"

#ifdef NDEBUG
    #define ARITH_LOG(type, msg, ...)
    #define ARITH_LOG_NO_CTX(type, msg, ...)
#else
    #define ARITH_LOG(type, msg, ...) log_ctx_impl(type, msg, __FILE__, __LINE__, ##__VA_ARGS__)
    #define ARITH_LOG_NO_CTX(type, msg, ...) log_impl(type, msg, ##__VA_ARGS__) // no file/line suffix
#endif

typedef enum LogType
{
    #ifdef __linux__
        LOG_ERROR = 91, // use enum as colours
        LOG_WARN = 93,
        LOG_INFO = 35
    #elif _WIN32
        LOG_ERROR = 12,
        LOG_WARN = 14,
        LOG_INFO = 13 
    #endif
} LogType;

void log_impl(LogType type, const char* msg, ...);

void log_ctx_impl(LogType type, const char* msg, const char* file, i32 line, ...);

#endif