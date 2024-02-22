#ifndef ARITH_COMPLEX_H
#define ARITH_COMPLEX_H

#include "defines.h"

#define COMPLEX_PRINCIPAL_ARG(z) 

// user will have to keep track of if polar or cartesian :/
typedef struct Complex
{
    union
    {
        struct // cartesian
        {
            f64 re;
            f64 im;
        };
        struct // polar
        {
            f64 mod;
            f64 arg;
        };
    };
    bool is_polar;
} Complex;

Complex complex_to_polar(Complex z);
Complex complex_to_cartesian(Complex z);

Complex complex_add(Complex z, Complex w);
Complex complex_subtract(Complex z, Complex w);
Complex complex_multiply(Complex z, Complex w);

Complex complex_pow(Complex z, u32 pow);

void complex_print(Complex z);

#endif