#include "test.h"

#include "defines.h"
#include <stdarg.h>
#include <stdio.h>

#ifdef __linux__
    #define FAILED_COLOUR 91
    #define PASSED_COLOUR 92
#elif _WIN32
    #include <windows.h>
    #define FAILED_COLOUR FOREGROUND_RED 
    #define PASSED_COLOUR FOREGROUND_GREEN
#endif

void test_impl(bool success, const char* msg, ...)
{
    va_list args;
    i32 colour;
    const char* prefix;

    if(success)
    {
        colour = PASSED_COLOUR;
        prefix = "[TEST PASSED]";
    }
    else
    {
        colour = FAILED_COLOUR;
        prefix = "[TEST FAILED]";
    }

    // set colour for prefix
    #ifdef __linux__
        printf("\x1B[%dm%s:\x1B[0m ", colour, prefix);
    #elif _WIN32
        CONSOLE_SCREEN_BUFFER_INFO cb_info;
        HANDLE console_handle = (output_stream == stderr)
                              ? GetStdHandle(STD_ERROR_HANDLE) : GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo(console_handle, &cb_info);
        i32 original_colour = cb_info.wAttributes;

        SetConsoleTextAttribute(console_handle, (WORD)colour);
            fprintf(output_stream, "%s: ", prefix);
        SetConsoleTextAttribute(console_handle, (WORD)original_colour);
    #endif

    va_start(args, msg);
        vprintf(msg, args);
    va_end(args);

    printf("\n");
}