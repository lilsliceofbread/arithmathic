#include "parser.h"

#include "defines.h"
#include "util.h"
#include "string.h"
#include "binary_tree.h"

// cool video by VoxelRifts on this: https://www.youtube.com/watch?v=myZcNjKcVGw

enum {
    PRECEDENCE_ZERO = 0,
    PRECEDENCE_AS = 1,
    PRECEDENCE_MD = 2,
    PRECEDENCE_I = 3,
};

static u8 precedence_table[OPERATOR_MAX] = {
    [OPERATOR_PLUS] = PRECEDENCE_AS,
    [OPERATOR_MINUS] = PRECEDENCE_AS,
    [OPERATOR_MULTIPLY] = PRECEDENCE_MD,
    [OPERATOR_DIVIDE] = PRECEDENCE_MD,
    [OPERATOR_POWER] = PRECEDENCE_I,
};

/**
 * internal functions
 */
TreeNode* parse_syntax_tree_node(TreeNode* prev, Token* tokens, u32 token_index, u8 last_operator_precedence);
void tokenise_number(u32* i, Token* curr_token, const char* expression);

f64 evaluate_expression(const char* expression, u32 str_length)
{
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

    f64 result = evaluate_syntax_tree(tree);

    if(tree != NULL)
    {
        binary_tree_free(tree);
    }
    return result;
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
                tokens[token_num].type = TOKEN_BRACKET;
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
    TreeNode* node = parse_syntax_tree_node(NULL, tokens, 0, 0); //! SHOULD LAST OP PRECEDENCE BE 0?

    //TreeNode* head = binary_tree_find_head(node);

    //*tree_out = head;
    return true;
}

double evaluate_syntax_tree(TreeNode* head)
{
    double eval = 0.0f;

    // evaluation

    return eval;
}

/**
 * internal functions
 */

TreeNode* parse_syntax_tree_node(TreeNode* prev, Token* tokens, u32 token_index, u8 last_operator_precedence)
{
    if(prev == NULL)
    {

    }

    //! USE STNode

    // recurse with new node as prev
    switch(tokens[token_index].type)
    {
        case TOKEN_NUM:
            break;

        case TOKEN_OPERATOR:
            break;

        case TOKEN_BRACKET:
            break;

        case TOKEN_EOF:
            break;
    }

    //WHAT IS BASE CASE
    //return parent/child node of prev
    //return ;
}

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