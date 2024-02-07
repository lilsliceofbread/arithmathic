#include "matrix.h"

#include <string.h>
#include <stdio.h>
#include "defines.h"

void matrix_transpose(matrix_t mat, u32 size)
{
    f32 new[size * size];

    for(u32 i = 0; i < size; i++)
    {
        for(u32 j = 0; j < size; j++)
        {
            new[i * size + j] = mat[j * size + i];
        }
    }
    
    memcpy(mat, new, size * size * sizeof(float));
}

void matrix_multiply(matrix_t out, const matrix_t mat1, const matrix_t mat2, u32 size)
{
    memset(out, 0, size * size * sizeof(float)); // set all floats in output matrix to zero

    for(u32 i = 0; i < size; i++)
    {
        for(u32 j = 0; j < size; j++)
        {
            u32 current_value = i * size + j;
            for(u32 k = 0; k < size; k++)
            {
                out[current_value] += mat1[k * size + j] * mat2[i * size + k];
            }
        }
    }
}

/* for debugging purposes */
void matrix_print(matrix_t mat, u32 size)
{
    char buffer[8192] = "matrix data\n";
    char* location = buffer + strlen(buffer);
    u32 strlength = (u32)strlen(buffer);

    ARITH_ASSERT(strlen(buffer) + (size * size * 6) + size + 1 <= 8192, "matrix size exceeded maximum characters\n");

    for(u32 i = 0; i < size; i++)
    {
        for(u32 j = 0; j < size; j++)
        {
            sprintf(location, " %.3f", mat[j * size + i]);
            location += 6;
        }
        strcat(buffer, "\n");
        location += 1;
    }
    *location++ = '\n';
    *location = '\0';

    ARITH_ASSERT(strlength + (size * size * 6) + size + 1 == strlen(buffer), "calculation is wrong: %u real is %u", strlength + (size * size * 6) + size, strlen(buffer));

    ARITH_LOG_NO_CTX(LOG_INFO, buffer);
}