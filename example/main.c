#include <stdio.h>
#include "defines.h"
#include "matrix.h"

int main(void)
{
    //char buffer[8192] = {0};
    //fgets(buffer, 8192, stdin);
    //printf("%s\n", buffer);

    //i32 eval = arith_evaluate_expression(buffer);

    //ARITH_LOG(LOG_INFO, "final result: %d", eval);

    // this should be a test
    MATRIX(mat1, 3, 3,
        1, 2, 3,
        4, 5, 6,
        7, 8, 9 
    );
    matrix_print(MATRIX_PTR(mat1));

    MATRIX(mat2, 3, 3,
        0, 0, 1,
        0, 1, 0,
        1, 0, 0
    );
    matrix_print(MATRIX_PTR(mat2));

    //MATRIX_CREATE_RESULT(result, mat1, mat2);
    MATRIX(result, 3, 3, 0);

    matrix_multiply(MATRIX_PTR(result), MATRIX_PTR(mat1), MATRIX_PTR(mat2));

    matrix_print(MATRIX_PTR(result));

    return 0;
}