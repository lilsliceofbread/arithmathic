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