#include "parser.h"

#include "defines.h"
#include "util.h"
#include "string.h"
#include "binary_tree.h"

/**
 * internal functions
 */
void tokenise_number(u32* i, Token* curr_token, const char* expression);

f64 evaluate_expression(const char* expression, u32 str_length)
{
    //f64 answer;
    Token tokens[str_length];
    TreeNode* tree = NULL;

    if(!tokenise_expression(tokens, str_length, expression))
    {
        return 0.0;
    }

    if(!generate_syntax_tree(tokens, &tree))
    {
        return 0.0;
    }

    if(tree != NULL)
    {
        binary_tree_free(tree);
    }
    //return answer;
    return 0.0;
}

bool tokenise_expression(Token* tokens, u32 length, const char* expression)
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
                tokens[token_num].type = TOKEN_NUM;
                tokenise_number(&i, &tokens[token_num], expression);
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
                tokens[token_num].type = TOKEN_BRACKET; // ! MUST CHECK IN TREE IF EMPTY BRACKETS
                tokens[token_num].str[0] = c;
                break;

            case ' ':
            case '\t':
            case '\n':
                token_num--; // bit scuffed, stops skipping tokens with whitespace
                break;

            case '\0':
                ARITH_LOG(LOG_INFO, "EOF on null character");
                tokens[token_num].type = TOKEN_EOF;
                return true;
    
            default:
                ARITH_LOG(LOG_ERROR, "failed to tokenise expression, invalid character\n");
                return false;
        }
        token_num++;
    }

    tokens[token_num].type = TOKEN_EOF;
    return true;
}

bool generate_syntax_tree(Token* tokens, TreeNode** tree_out)
{
    TreeNode* curr_node = NULL;

    //for()
    //node create token no parent


    //*tree_out = node; // HEAD NODE
    return true;
}

/**
 * internal functions
 */
void tokenise_number(u32* i, Token* curr_token, const char* expression)
{
    char c = expression[*i];

    bool still_number = true;
    u32 number_length = 0;
    while(still_number)
    {
        curr_token->str[number_length++] = c;
        c = expression[++(*i)];
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
    --(*i);
}