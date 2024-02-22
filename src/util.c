#include "util.h"

#include "defines.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// windows is fucking dumb
#ifdef __linux__
    #define GET_LAST_FILE_SEPARATOR(name) char* name = str_find_last_of(path, '/')
#elif _WIN32
    #define GET_LAST_FILE_SEPARATOR(name) char* last_slash = str_find_last_of(path, '/'); char* last_backslash = str_find_last_of(path, '\\'); char* name = last_slash > last_backslash ? last_slash : last_backslash
#endif

char* str_find_last_of(const char* str, char c)
{
    if(str == NULL) return NULL;

    char* curr = (char*)str; // discarding const but not modifying the string
    char* latest_occurrence = NULL;

    while(*curr != '\0')
    {
        if(*curr == c) latest_occurrence = curr;
        curr++;
    }

    return latest_occurrence;
}

void find_directory_from_path(char* buffer, u32 length, const char* path)
{
    GET_LAST_FILE_SEPARATOR(last_char);
    ARITH_ASSERT(last_char != NULL, "invalid path %s\n", path);
    u32 offset = (u32)(last_char - path);

    u32 str_end = offset < length ? offset : length;
    strncpy(buffer, path, str_end); // copy up to final / into directory
    buffer[str_end] = '\0';
}

void find_file_from_path(char* buffer, u32 length, const char* path)
{
    GET_LAST_FILE_SEPARATOR(last_char);

    if(last_char == NULL)
    {
        strncpy(buffer, path, length);
        buffer[length - 1] = '\0'; // just in case
        return;
    }

    if(strlen(last_char) <= 1) // don't use ASSERT since this function is used in LOG
    {
        printf("find_file_from_path(): no file in path");
        DEBUG_BREAK();
    }

    strncpy(buffer, last_char + 1, length);
    buffer[length - 1] = '\0'; // just in case
}