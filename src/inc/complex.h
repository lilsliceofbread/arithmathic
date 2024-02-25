#ifndef ARITH_COMPLEX_H
#define ARITH_COMPLEX_H

#include "defines.h"
#include "math.h"

#define COMPLEX_PRINCIPAL_ARG(arg) arg = (arg > ARITH_PI || arg < -ARITH_PI) ? arg - (2 * ARITH_PI * (int)(arg / (2 * ARITH_PI))) : arg

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

static inline f64 complex_modulus(Complex z)
{
    return z.is_polar ? z.mod : sqrt(z.re * z.re + z.im * z.im);
}

Complex complex_conjugate(Complex z);

void complex_to_polar(Complex* z);
void complex_to_cartesian(Complex* z);

/**
 * @returns cartesian form
 * */
Complex complex_add(Complex z, Complex w);

/**
 * @returns cartesian form
 * */
Complex complex_subtract(Complex z, Complex w);

/**
 * @returns polar form if both z and w were polar and cartesian otherwise 
 * */
Complex complex_multiply(Complex z, Complex w);

/**
 * @returns polar form if both z and w were polar and cartesian otherwise 
 * */
Complex complex_divide(Complex z, Complex w);

/**
 * @returns polar form if both z and w were polar and cartesian otherwise 
 * */
Complex complex_pow(Complex z, f64 power);

void complex_print(Complex z);

#endif