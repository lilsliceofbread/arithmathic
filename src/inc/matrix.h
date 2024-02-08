#ifndef ARITH_MATRIX_H
#define ARITH_MATRIX_H

#include "types.h"

typedef u32* matrix_t; // ptr to the first 2 elements of the matrix struct, the width and height
//typedef struct {u32 w; u32 h; f32* data;} matrix_t;

#define MATRIX_PTR(matrix) (matrix_t)&(matrix)

/**
 * a bit cursed but allows specifying matrix value visually column major while also being memory column major
*/
#define MATRIX(var_name, width, height, ...)                      \
    struct {u32 w; u32 h; f32 data[width * height];} var_name = { \
        .w = (width),                                             \
        .h = (height),                                            \
        .data = {__VA_ARGS__},                                    \
    };                                                            \
    matrix_transpose(MATRIX_PTR(var_name))

#define MATRIX_CREATE_RESULT(var_name, mat1, mat2) MATRIX(var_name, mat1.h, mat2.w, 0)

/**
 * @param  mat: matrix to be transposed
 * @param  size: all matrices must be square matrices of size size
 */
void matrix_transpose(matrix_t mat);

/**
 * @param  out: destination of multiplication
 * @param  size: all matrices must be square matrices of size size
 */
void matrix_multiply(matrix_t out, const matrix_t mat1, const matrix_t mat2);

/* for debugging purposes */
void matrix_print(matrix_t mat);

#endif
