#include "arith_matrix_test.h"

#include "defines.h"
#include "matrix.h"

bool test_matrix_creation(void)
{
    MATRIX(mat, 4, 2,
        1, 5,
        2, 6,
        3, 7,
        4, 8
    );

    if(!(mat.data[0] == 1.0f && mat.data[4] == 5.0f &&
         mat.data[1] == 2.0f && mat.data[5] == 6.0f &&
         mat.data[2] == 3.0f && mat.data[6] == 7.0f &&
         mat.data[3] == 4.0f && mat.data[7] == 8.0f))
    {
        return false;
    }

    // ! add more

    return true;
}

bool test_matrix_multiply(void)
{
    MATRIX(mat1, 3, 3,
        1, 2, 3,
        4, 5, 6,
        7, 8, 9 
    );

    MATRIX(mat2, 3, 2,
        1, 4,
        2, 5,
        3, 6
    );

    MATRIX(result, 3, 2, 0);

    matrix_multiply(MATRIX_PTR(result), MATRIX_PTR(mat1), MATRIX_PTR(mat2));

    if(!(result.data[0] == 14.0f && result.data[3] == 32.0f &&
         result.data[1] == 32.0f && result.data[4] == 77.0f &&
         result.data[2] == 50.0f && result.data[5] == 122.0f))
    {
        return false;
    }

    // ! add more

    return true;
}