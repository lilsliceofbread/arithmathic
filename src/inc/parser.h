#ifndef ARITH_PARSER_H
#define ARITH_PARSER_H

#include "defines.h"

#define MAX_TOKEN_LENGTH 32

typedef enum TokenType
{
    TOKEN_NUM,
    TOKEN_OPERATOR, // operator operates on numbers on either side?
    TOKEN_BRACKET, // open and closed bracket separate?
} TokenType;

typedef struct Token
{
    char str[MAX_TOKEN_LENGTH];
    TokenType type;
} Token;

f64 evaluate_expression(const char* expression, u32 str_length);

#endif