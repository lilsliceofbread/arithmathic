#include "parser.h"

#include "defines.h"
#include "util.h"
#include "string.h"
#include "binary_tree.h"

f64 evaluate_expression(const char* expression, u32 str_length)
{
    //f64 answer;
    Token tokens[str_length];
    u32 token_count = 0;
    TreeNode* tree;

    if(!tokenise_expression(tokens, str_length, expression, &token_count))
    {
        return 0.0;
    }

    if(!generate_syntax_tree(&tree, tokens, token_count))
    {
        return 0.0;
    }

    binary_tree_free(tree);
    //return answer;
    return 0.0;
}

bool tokenise_expression(Token* tokens, u32 length, const char* expression, u32* token_count_out)
{
    memset(tokens, 0, length * sizeof(Token)); // ensure all strings are zeroed so string ends 

    u32 token_num = 0;

    for(u32 i = 0; i < length; i++)
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
                *token_count_out = token_num;
                return true;
    
            default:
                ARITH_LOG(LOG_ERROR, "failed to tokenise expression, invalid character\n");
                *token_count_out = 0;
                return false;
        }
        token_num++;
    }

    *token_count_out = token_num;
    return true;
}

bool generate_syntax_tree(TreeNode** tree_out, Token* tokens, u32 token_count)
{
    // zero is top of syntax tree i think?
    // because it's the answer to the expression
    binary_tree_create(tree_out, NULL, sizeof(Token)); // don't know what to put for size of data, float or Token

    return true;
}