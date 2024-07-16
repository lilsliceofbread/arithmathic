#include "arith_parser_test.h"
#include "parser.h"
#include <string.h>

bool test_tokenise_expression(void)
{
    const char* expression = "(123 + 456) / 2";
    u32 length = (u32)strlen(expression);
    Token tokens[length];

    Token expected_tokens[8] = {
        {.type = TOKEN_BRACKET, .str = "("},
        {.type = TOKEN_NUM, .str = "123"},
        {.type = TOKEN_OPERATOR, .str = "+"},
        {.type = TOKEN_NUM, .str = "456"},
        {.type = TOKEN_BRACKET, .str = ")"},
        {.type = TOKEN_OPERATOR, .str = "/"},
        {.type = TOKEN_NUM, .str = "2"},
        {.type = TOKEN_EOF, .str = ""},
    };
    tokenise_expression(tokens, length, expression);

    for(u32 i = 0; i < 8; i++)
    {
        if(tokens[i].type == expected_tokens[i].type
        && strcmp(tokens[i].str, expected_tokens[i].str) == 0)
        {
            continue;
        }

        return false; // * found not to match
    }

    return true;
}

bool test_evaluate_expression(void)
{
    const char* expression = "1 / 3 *3 - 4 + 3/ 3";

    f64 result = evaluate_expression(expression, (u32)strlen(expression));
    if(result != -2.0) return false;

    // * testing if returns 0 with invalid expression, will cause an ERROR to be printed
    expression = "1 -";
    result = evaluate_expression(expression, (u32)strlen(expression));
    if(result != 0.0) return false;

    return true;
}