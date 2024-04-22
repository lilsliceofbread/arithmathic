#include <stdio.h>
#include <string.h>
#include "defines.h"

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

    //evaluate_expression(expression, MAX_CHAR_LENGTH);
    return 0;
}