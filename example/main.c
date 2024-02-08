#include <stdio.h>
#include "defines.h"
#include "matrix.h"

int main(void)
{
    MATRIX(mat1, 3, 3,
        1, 2, 3,
        4, 5, 6,
        7, 8, 9 
    );
    matrix_print(MATRIX_PTR(mat1));

    MATRIX(mat2, 3, 2,
        1, 4,
        2, 5,
        3, 6
    );
    matrix_print(MATRIX_PTR(mat2));

    MATRIX(result, 3, 2, 0);

    matrix_multiply(MATRIX_PTR(result), MATRIX_PTR(mat1), MATRIX_PTR(mat2));

    matrix_print(MATRIX_PTR(result));

    return 0;
}