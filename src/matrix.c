#include "matrix.h"

#include <string.h>
#include <stdio.h>
#include "defines.h"

#define MATRIX_GET_STRUCT(mat_ptr) \
    struct {u32 w; u32 h; f32 data[(*(u32*)mat_ptr) * ((u32*)mat_ptr)[1]];}* _##mat_ptr = mat_ptr

void matrix_transpose(matrix_t mat)
{
    MATRIX_GET_STRUCT(mat);

    f32 new[_mat->w * _mat->h];
    u32 width = _mat->w;
    u32 height = _mat->h;

    for(u32 i = 0; i < height; i++)
    {
        for(u32 j = 0; j < width; j++)
        {
            new[i * width + j] = mat[j * height + i];
        }
    }
    
    _mat->w = height;
    _mat->h = width;
    memcpy(&_mat->data, &new, width * height * sizeof(float));
}

void matrix_multiply(matrix_t out, const matrix_t mat1, const matrix_t mat2)
{
    MATRIX_GET_STRUCT(mat1);
    MATRIX_GET_STRUCT(mat2);
    MATRIX_GET_STRUCT(out);

    if(_mat2->h != _mat1->w)
    {
        ARITH_LOG(LOG_ERROR, "incompatible matrices for multiplication. dimensions: h w\n mat1: %u %u\n mat2: %u %u\n",
                  _mat1->h, _mat1->w, _mat2->h, _mat2->w);
        return;
    }

    if(_out->w != _mat2->w || _out->h != _mat1->h)
    {
        ARITH_LOG(LOG_ERROR, "wrong dimensions for result matrix of multiplication. dimensions: h w\n expected: %u %u\n got: %u %u\n",
                  _mat1->h, _mat2->w, _out->h, _out->w);
        return;
    }

    memset(out, 0, _out->w * _out->h * sizeof(float)); // set all floats in output matrix to zero

    for(u32 i = 0; i < _out->h; i++)
    {
        for(u32 j = 0; j < _out->w; j++)
        {
            u32 current_value = i * _out->h + j;
            for(u32 k = 0; k < _mat1->w /* or _mat2->h */; k++)
            {
                out[current_value] += _mat1->data[k * _mat1->h + j] * _mat2->data[i * _mat2->h + k];
            }
        }
    }
}

/* for debugging purposes */
void matrix_print(matrix_t mat)
{
    MATRIX_GET_STRUCT(mat);

    u32 width = _mat->w;
    u32 height = _mat->h;

    char buffer[8192] = "matrix data\n";
    char* location = buffer + strlen(buffer);
    u32 strlength = (u32)strlen(buffer);

    ARITH_ASSERT(strlen(buffer) + (width * height * 6) + height + 1 <= 8192, "matrix size exceeded maximum characters\n");

    for(u32 i = 0; i < height; i++)
    {
        for(u32 j = 0; j < width; j++)
        {
            sprintf(location, " %.3f", mat[j * height + i]);
            location += 6;
        }
        strcat(buffer, "\n");
        location += 1;
    }
    *location++ = '\n';
    *location = '\0';

    ARITH_ASSERT(strlength + (width * height * 6) + height + 1 == strlen(buffer), "calculation is wrong: %u real is %u", strlength + (width * height * 6) + height, strlen(buffer));

    ARITH_LOG_NO_CTX(LOG_INFO, buffer);
}