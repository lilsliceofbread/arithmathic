#include "matrix.h"

#include <string.h>
#include <stdio.h>
#include "defines.h"

#define MAX_CHARS 8192

#define MATRIX_GET_STRUCT(mat_ptr)                     \
    struct {u32* w; u32* h; f32* data;} _##mat_ptr = { \
        .w = &((u32*)mat_ptr)[0],                      \
        .h = &((u32*)mat_ptr)[1],                      \
        .data = &((f32*)mat_ptr)[2],                   \
    };
void matrix_transpose(matrix_t mat)
{
    MATRIX_GET_STRUCT(mat);

    u32 width = *_mat.w;
    u32 height = *_mat.h;
    f32 new[width * height];

    for(u32 i = 0; i < height; i++)
    {
        for(u32 j = 0; j < width; j++)
        {
            new[i * width + j] = _mat.data[j * height + i];
        }
    }
    
    *_mat.w = height;
    *_mat.h = width;
    memcpy(_mat.data, &new, width * height * sizeof(float));
}

void matrix_multiply(matrix_t out, const matrix_t mat1, const matrix_t mat2)
{
    MATRIX_GET_STRUCT(mat1);
    MATRIX_GET_STRUCT(mat2);
    MATRIX_GET_STRUCT(out);

    u32 mat1_w = *_mat1.w;
    u32 mat1_h = *_mat1.h;
    u32 mat2_w = *_mat2.w;
    u32 mat2_h = *_mat2.h;
    u32 out_w = *_out.w;
    u32 out_h = *_out.h;

    if(mat2_h != mat1_w)
    {
        ARITH_LOG(LOG_ERROR, "incompatible matrices for multiplication. dimensions: h w\n mat1: %u %u\n mat2: %u %u\n",
                  mat1_h, mat1_w, mat2_h, mat2_w);
        return;
    }

    if(out_w != mat2_w || out_h != mat1_h)
    {
        ARITH_LOG(LOG_ERROR, "wrong dimensions for result matrix of multiplication. dimensions: h w\n expected: %u %u\n got: %u %u\n",
                  mat1_h, mat2_w, out_h, out_w);
        return;
    }

    memset(_out.data, 0, out_w * out_h * sizeof(float)); // set all floats in output matrix to zero

    /* out(j, i) = sum of mat1(j, k) * mat2(k, i) */
    for(u32 i = 0; i < out_w; i++)
    {
        for(u32 j = 0; j < out_h; j++)
        {
            u32 current_value = i * out_h + j;
            for(u32 k = 0; k < mat1_w /* or mat2_h */; k++)
            {
                _out.data[current_value] += _mat1.data[k * mat1_h + j] * _mat2.data[i * mat2_h + k];
            }
        }
    }
}

void matrix_print(matrix_t mat)
{
    MATRIX_GET_STRUCT(mat);

    u32 width = *_mat.w;
    u32 height = *_mat.h;

    char buffer[MAX_CHARS] = {0};
    snprintf(buffer, MAX_CHARS, "matrix data\n dimensions: %u %u\n", height, width);
    u32 str_length = (u32)strlen(buffer);

    for(u32 i = 0; i < height; i++)
    {
        for(u32 j = 0; j < width; j++)
        {
            snprintf(buffer + str_length, MAX_CHARS - str_length, " %.3f", _mat.data[j * height + i]);
            str_length += (u32)strlen(buffer + str_length);
        }
        strncat(buffer, "\n", MAX_CHARS - str_length);
        str_length++;
    }
    strncat(buffer, "\n\0", MAX_CHARS - str_length);

    ARITH_LOG_NO_CTX(LOG_INFO, buffer);
}