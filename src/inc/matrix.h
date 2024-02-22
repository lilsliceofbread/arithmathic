#ifndef ARITH_MATRIX_H
#define ARITH_MATRIX_H

/**
 * the way this is implemented, the matrices are compile time
 * so you can't have a runtime defined size for matrices
 */
#include "types.h"

typedef u32* matrix_t; // ptr to the first 2 elements of the matrix struct, the width and height

#define MATRIX_PTR(matrix) (matrix_t)&(matrix)

/**
 * a bit cursed but allows specifying matrix value visually column major while also being memory column major
 * and having it evaluate at compile time
 * have to swap height and width because mat_transpose will swap them
*/
#define MATRIX(var_name, height, width, ...)                      \
    struct {u32 w; u32 h; f64 data[width * height];} var_name = { \
        .w = (height),                                            \
        .h = (width),                                             \
        .data = {__VA_ARGS__},                                    \
    };                                                            \
    matrix_transpose(MATRIX_PTR(var_name))

//#define MATRIX_MUTABLE(var_name, heat, width, ...)

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

void matrix_print(matrix_t mat);

#endif
