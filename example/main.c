#include <stdio.h>
#include "defines.h"
#include "matrix.h"

int main(void)
{
    MATRIX(mat1, 3, 
        1, 2, 3,
        4, 5, 6,
        7, 8, 9 
    );
    matrix_print(mat1, 3);

    MATRIX(mat2, 3,
        0, 0, 1,
        0, 1, 0,
        1, 0, 0
    );
    matrix_print(mat2, 3);

    // 0 sets matrix to zero matrix
    MATRIX(result, 3, 0);

    matrix_multiply(result, mat1, mat2, 3);

    matrix_print(result, 3);

    return 0;
}