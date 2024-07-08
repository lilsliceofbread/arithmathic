#ifndef ARITH_PARSER_H
#define ARITH_PARSER_H

#include "defines.h"

#include "binary_tree.h"

#define MAX_TOKEN_LENGTH 32

typedef enum TokenType
{
    TOKEN_NUM,
    TOKEN_OPERATOR,
    TOKEN_BRACKET,
    TOKEN_EOF,
} TokenType;

typedef struct Token
{
    char str[MAX_TOKEN_LENGTH];
    TokenType type;
} Token;

typedef enum Operator
{
    OPERATOR_PLUS,
    OPERATOR_MINUS,
    OPERATOR_MULTIPLY,
    OPERATOR_DIVIDE,
    OPERATOR_POWER,
    OPERATOR_MAX,
} Operator;

typedef union STNode
{
    f64 number;
    Operator operator;
};

f64 evaluate_expression(const char* expression, u32 str_length);

/**
 * @param  length: max length of expression string and of tokens buffer (should be same length for worst case e.g. 1+1+1+1+1...)
 */
bool tokenise_expression(Token* tokens, u32 length, const char* expression);

/**
 * @param  tree_out: returns head node of tree
 */
bool generate_syntax_tree(Token* tokens, TreeNode** tree_out);

double evaluate_syntax_tree(TreeNode* head);

#endif