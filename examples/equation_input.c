#include <stdio.h>
#include <string.h>
#include "defines.h"
#include "parser.h"

#define MAX_CHAR_LENGTH 256

int main(void)
{
    char expression[MAX_CHAR_LENGTH];
    memset(expression, 0, MAX_CHAR_LENGTH);

    printf("Enter an expression to be evaluated (e.g. 1 + 3 / 5):");
    if(fgets(expression, MAX_CHAR_LENGTH, stdin) == NULL)
    {
        ARITH_LOG(LOG_ERROR, "could not get input string\n");
        return -1;
    }

    f64 result = evaluate_expression(expression, MAX_CHAR_LENGTH);
    printf("Expression result: %lf\n", result);
    return 0;
}