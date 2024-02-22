#include "complex.h"
#include <math.h>

Complex complex_to_polar(Complex z)
{
    Complex c;
    
    c.mod = sqrt(z.re * z.re + z.im * z.im);
    c.arg = atan2(z.im, z.re);

    return c;
}

Complex complex_to_cartesian(Complex z)
{
    Complex c;
    
    c.re = z.mod * cos(z.arg);
    c.im = z.mod * sin(z.arg);

    return c;
}

Complex complex_add(Complex z, Complex w)
{
    Complex c;
    c.is_polar = false; // no polar when adding

    if(z.is_polar)
    {
        z = complex_to_cartesian(z);
    }
    if(w.is_polar)
    {
        w = complex_to_cartesian(w);
    }

    c.re = z.re + w.re;
    c.im = z.im + w.im;

    return c;
}

Complex complex_subtract(Complex z, Complex w)
{
    Complex c;
    c.is_polar = false; // no polar when adding

    if(z.is_polar)
    {
        z = complex_to_cartesian(z);
    }
    if(w.is_polar)
    {
        w = complex_to_cartesian(w);
    }

    c.re = z.re - w.re;
    c.im = z.im - w.im;

    return c;
}

Complex complex_multiply(Complex z, Complex w)
{
    Complex c = {0};
    c.is_polar = false;

    if(z.is_polar && w.is_polar)
    {
        c.is_polar = true;
        c.mod = z.mod * w.mod;
        c.arg = z.arg + w.arg;

        return c;
    }

    if(z.is_polar)
    {
        z = complex_to_cartesian(z);
    }
    if(w.is_polar)
    {
        w = complex_to_cartesian(w);
    }

    c.re += z.re * w.re;

    c.im += z.re * w.im;
    c.im += z.im * w.re;

    c.re -= z.im * w.im; // i^2 = -1

    return c;
}

Complex complex_pow(Complex z, u32 power)
{
    if(z.is_polar) // de moivre's theorem
    {
        Complex c = {
            .mod = pow(z.mod, (f64)power),
            .arg = (f64)power * z.arg,
            .is_polar = true,
        };

        return c;
    }

    if(power == 0) // somehow
    {
        Complex c = { // this works for polar or cartesian
            .re = 1.0,
            .im = 0.0,
            .is_polar = z.is_polar,
        };

        return c;
    }
    if(power == 1) return z;

    return complex_multiply(z, complex_pow(z, power - 1));
}

void complex_print(Complex z)
{
    if(z.is_polar)
    {
        ARITH_LOG_NO_CTX(LOG_INFO, "Complex number: %lfcis(%lf)\n", z.mod, z.arg);
        return;
    }

    const char* sign = " + ";
    if(z.im < 0)
    {
        sign = " - ";
        z.im = fabs(z.im);
    }

    ARITH_LOG_NO_CTX(LOG_INFO, "Complex number: %lf%s%lfi\n", z.re, sign, z.im);
}