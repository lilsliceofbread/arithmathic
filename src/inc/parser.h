#ifndef ARITH_PARSER_H
#define ARITH_PARSER_H

#include "defines.h"

#include "binary_tree.h"

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

/**
 * internal functions; in header to be testable
 */
/**
 * @param  length: max length of expression string and of tokens buffer (should be same length for worst case e.g. 1+1+1+1+1...)
 * @returns token count
 */
bool tokenise_expression(Token* tokens, u32 length, const char* expression, u32* token_count_out);

bool generate_syntax_tree(TreeNode** tree_out, Token* tokens, u32 token_count);

#endif