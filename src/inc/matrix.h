#ifndef ARITH_MATRIX_H
#define ARITH_MATRIX_H

// ONLY FOR SQUARE MATRICES

#include "types.h"

typedef f32* matrix_t;

// bit cringe but allows specifying matrix value visually column major while also being memory column major
#define MATRIX(var_name, n, ...) f32 var_name[n * n] = {__VA_ARGS__}; matrix_transpose(var_name, n)

/**
 * @param  mat: matrix to be transposed
 * @param  size: all matrices must be square matrices of size size
 */
void matrix_transpose(matrix_t mat, u32 size);

/**
 * @param  out: destination of multiplication
 * @param  size: all matrices must be square matrices of size size
 */
void matrix_multiply(matrix_t out, const matrix_t mat1, const matrix_t mat2, u32 size);

/* for debugging purposes */
void matrix_print(matrix_t mat, u32 size);

#endif