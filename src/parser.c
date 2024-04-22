#include "parser.h"
#include "util.h"

/**
 * internal functions
 */

/**
 * @param  length: max length of expression string and of tokens buffer
 */
bool lex_expression(Token* buffer_out, const char* expression, u32 length);

f64 evaluate_expression(const char* expression, u32 str_length)
{
    f64 answer;
    Token tokens[str_length];

    if(!lex_expression(tokens, expression, str_length))
    {
        ARITH_LOG(LOG_ERROR, "could not lex expression\n");
        return 0.0;
    }

    return answer;
}

bool lex_expression(Token* buffer_out, const char* expression, u32 length)
{
    const char* cursor = expression;
    u32 token_num = 0;
    u32 token_cursor = 0;
    for(u32 i = 0; i < length; i++)
    {
        switch(*cursor)
        {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '.':
                buffer_out[token_num].str[token_cursor++] = *cursor;
                buffer_out[token_num].type = TOKEN_NUM; // will do this multiple times if number is 2+ characters but that is fine
                break;

            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
                token_num++; // * operator always means new token
                token_cursor = 0;
                buffer_out[token_num].str[token_cursor] = *cursor;
                buffer_out[token_num].type = TOKEN_OPERATOR;
                break;

            case '(':
            case ')':
                token_num++; // * bracket always means new token
                token_cursor = 0;
                buffer_out[token_num].str[token_cursor] = *cursor;
                buffer_out[token_num].type = TOKEN_BRACKET;
                break;

            case ' ':
            case '\t':
                token_num++;
                token_cursor = 0;
                skip_whitespace(&cursor, length - (u32)(cursor - expression + 1));
                break;

            case '\0':
            case '\n': // ! newline will end lexing, unsure about this
                goto lexer_end;

            default:
                ARITH_LOG(LOG_ERROR, "failed to lex expression, invalid character\n");
                return false;
        }
        cursor++;

        ARITH_ASSERT(cursor - expression + 1 > length, "exceeded length of string\n");
    }
    lexer_end: ;

    return true;
}