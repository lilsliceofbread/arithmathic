#include "parser.h"
#include "util.h"

/**
 * internal functions
 */

/**
 * @param  length: max length of expression string and of tokens buffer
 */
bool tokenise_expression(Token* tokens, u32 length, const char* expression);

f64 evaluate_expression(const char* expression, u32 str_length)
{
    //f64 answer;
    Token tokens[str_length];

    if(!tokenise_expression(tokens, str_length, expression))
    {
        return 0.0;
    }

    for(u32 i = 0; i < 15; i++)
    {
        const char* type;
        switch(tokens[i].type)
        {
            case TOKEN_NUM:
                type = "NUM";
                break;
            case TOKEN_OPERATOR:
                type = "OPERATOR";
                break;
            case TOKEN_BRACKET:
                type = "BRACKET";
                break;
        }

        ARITH_LOG(LOG_INFO, "%u %s: %s", i, type, tokens[i].str);
    }

    //return answer;
    return 0.0;
}

bool tokenise_expression(Token* tokens, u32 length, const char* expression)
{
    u32 token_num = 0;
    for(u32 i = 0; i < length - 2; i++)
    {
        char c = expression[i];
        switch(c)
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
                bool still_number = true; // TODO: put in own function
                u32 number_length = 0;
                tokens[token_num].type = TOKEN_NUM; // will do this multiple times if number is 2+ characters but that is fine
                while(still_number)
                {
                    tokens[token_num].str[number_length++] = c;
                    c = expression[++i];
                    switch(c)
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
                            break;
                        default:
                            still_number = false;
                    }
                }
                i--;
                break;

            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
                tokens[token_num].type = TOKEN_OPERATOR;
                tokens[token_num].str[0] = c;
                break;

            case '(':
            case ')':
                tokens[token_num].type = TOKEN_BRACKET; // ! MUST CHECK IN TREE IF EMPTY BRACKETS OR 2 BRACKET LEVELS (OPEN OR CLOSE BRACKET IMPORTANT)
                tokens[token_num].str[0] = c;
                break;

            case ' ':
            case '\t':
                token_num--; // bit scuffed, stops skipping tokens with whitespace
                break;

            case '\0':
            case '\n':
                ARITH_LOG(LOG_INFO, "ended on newline or null character in tokenisation\n");
                return true;
    
            default:
                ARITH_LOG(LOG_ERROR, "failed to tokenise expression, invalid character\n");
                return false;
        }
        token_num++;
    }

    return true;
}