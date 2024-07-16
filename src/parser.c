#include "parser.h"

#include <stdio.h>
#include <math.h>
#include <string.h>
#include "defines.h"
#include "util.h"
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
TreeNode* parse_syntax_tree_node(Token* tokens, u32* token_index, u8 last_operator_precedence);
void tokenise_number(u32* i, Token* curr_token, const char* expression);
Operator operator_from_token(Token token);

f64 evaluate_expression(const char* expression, u32 str_length)
{
    Token tokens[str_length + 1];
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
    u32 token_index = 0; // also scuffed but idc
    TreeNode* node = parse_syntax_tree_node(tokens, &token_index, PRECEDENCE_ZERO);

    if(node == NULL) return false;

    TreeNode* head = binary_tree_find_head(node);

    *tree_out = head;

    return true;
}

double evaluate_syntax_tree(TreeNode* head)
{
    STNode node = *(STNode*)(head->data);
    if(node.type == NODE_NUM)
    {
        return node.number;
    }

    switch(node.operator)
    {
        case OPERATOR_PLUS:
            return evaluate_syntax_tree(head->left) + evaluate_syntax_tree(head->right);
        case OPERATOR_MINUS:
            return evaluate_syntax_tree(head->left) - evaluate_syntax_tree(head->right);
        case OPERATOR_MULTIPLY:
            return evaluate_syntax_tree(head->left) * evaluate_syntax_tree(head->right);
        case OPERATOR_DIVIDE:
            return evaluate_syntax_tree(head->left) / evaluate_syntax_tree(head->right);
        case OPERATOR_POWER:
            return pow(evaluate_syntax_tree(head->left), evaluate_syntax_tree(head->right));
    }

    return 0.0;
}

/**
 * internal functions
 */

TreeNode* parse_syntax_tree_node(Token* tokens, u32* token_index, u8 last_operator_precedence)
{
    if(tokens[*token_index].type != TOKEN_NUM)
    {
        ARITH_LOG(LOG_ERROR, "expected number token type");
        return NULL; //! leaks memory but idc anymore
    }

    TreeNode* left = NULL;
    STNode node;
    node.type = NODE_NUM;
    node.number = strtod(tokens[*token_index].str, NULL);
    binary_tree_node_create(&left, NULL, (void*)&node, sizeof(STNode));
    (*token_index)++;

    if(tokens[*token_index].type != TOKEN_OPERATOR)
    {
        if(tokens[*token_index].type == TOKEN_EOF) return left;

        ARITH_LOG(LOG_ERROR, "expected operator token type");
        return NULL;
    }

    Operator curr_operator = operator_from_token(tokens[*token_index]);
    u8 curr_operator_precedence = precedence_table[curr_operator];

    while(curr_operator_precedence != PRECEDENCE_ZERO)
    {
        if(last_operator_precedence >= curr_operator_precedence)
        {
            break;    
        }
        else
        {
            (*token_index)++;

            TreeNode* parent = NULL;
            node.type = NODE_OPERATOR;
            node.operator = curr_operator;
            binary_tree_node_create(&parent, NULL, (void*)&node, sizeof(STNode));

            parent->left = left;
            parent->right = parse_syntax_tree_node(tokens, token_index, curr_operator_precedence);
            if(parent->right == NULL) return NULL; // also scuffed

            left = parent;

            if(tokens[*token_index].type != TOKEN_OPERATOR)
            {
                if(tokens[*token_index].type == TOKEN_EOF) return left;

                ARITH_LOG(LOG_ERROR, "expected operator token type");
                return NULL;
            }
            curr_operator = operator_from_token(tokens[*token_index]);
            curr_operator_precedence = precedence_table[curr_operator];
        }
    }

    return left;
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

Operator operator_from_token(Token token)
{
    if(token.type != TOKEN_OPERATOR)
    {
        ARITH_LOG(LOG_ERROR, "trying to obtain operator from non-operator token\n");
    }

    switch(token.str[0])
    {
        case '+':
            return OPERATOR_PLUS;
        case '-':
            return OPERATOR_MINUS;
        case '*':
            return OPERATOR_MULTIPLY;
        case '/':
            return OPERATOR_DIVIDE;
        case '^':
            return OPERATOR_POWER;
    }

    return OPERATOR_MAX;
}