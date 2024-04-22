#ifndef ARITH_UTIL_H
#define ARITH_UTIL_H

#include "types.h"

char* str_find_last_of(const char* str, char c);

void find_directory_from_path(char* buffer, u32 length, const char* path);

void find_file_from_path(char* buffer, u32 length, const char* path);

void skip_whitespace(const char** cursor, u32 max_distance);

#endif