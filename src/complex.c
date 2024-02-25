#include "complex.h"
#include <math.h>

Complex complex_conjugate(Complex z)
{
    Complex c = z;
    c.im = -c.im; // works for polar form as well
    return c;
}

void complex_to_polar(Complex* z)
{
    if(z->is_polar) return;
    Complex c;
    
    c.mod = complex_modulus(*z);
    c.arg = atan2(z->im, z->re);
    COMPLEX_PRINCIPAL_ARG(c.arg);

    c.is_polar = true;
    *z = c;
}

void complex_to_cartesian(Complex* z)
{
    if(!z->is_polar) return;
    Complex c;
    
    c.re = z->mod * cos(z->arg);
    c.im = z->mod * sin(z->arg);

    c.is_polar = false;
    *z = c;
}

Complex complex_add(Complex z, Complex w)
{
    Complex c;

    if(z.is_polar)
    {
        complex_to_cartesian(&z);
    }
    if(w.is_polar)
    {
        complex_to_cartesian(&w);
    }

    c.re = z.re + w.re;
    c.im = z.im + w.im;
    c.is_polar = false; // no polar when adding

    return c;
}

Complex complex_subtract(Complex z, Complex w)
{
    Complex c;

    if(z.is_polar)
    {
        complex_to_cartesian(&z);
    }
    if(w.is_polar)
    {
        complex_to_cartesian(&w);
    }

    c.re = z.re - w.re;
    c.im = z.im - w.im;
    c.is_polar = false; // no polar when adding

    return c;
}

Complex complex_multiply(Complex z, Complex w)
{
    bool should_be_cartesian = false;

    if(!z.is_polar)
    {
        complex_to_polar(&z);
        should_be_cartesian = true;
    }
    if(!w.is_polar)
    {
        complex_to_polar(&w);
        should_be_cartesian = true;
    }

    Complex c = {
        .mod = z.mod * w.mod,
        .arg = z.arg + w.arg,
        .is_polar = true,
    };
    COMPLEX_PRINCIPAL_ARG(c.arg);

    if(should_be_cartesian) complex_to_cartesian(&c);

    return c;
}

Complex complex_divide(Complex z, Complex w)
{
    bool should_be_cartesian = false;

    if(!z.is_polar)
    {
        complex_to_polar(&z);
        should_be_cartesian = true;
    }
    if(!w.is_polar)
    {
        complex_to_polar(&w);
        should_be_cartesian = true;
    }

    Complex c = {
        .mod = z.mod * w.mod,
        .arg = z.arg + w.arg,
        .is_polar = true,
    };
    COMPLEX_PRINCIPAL_ARG(c.arg);

    if(should_be_cartesian) complex_to_cartesian(&c);

    return c;
}

Complex complex_pow(Complex z, f64 power)
{
    bool should_be_cartesian = false;

    if(!z.is_polar)
    {
        complex_to_polar(&z);
        should_be_cartesian = true;
    }

    Complex c = { // de moivre's theorem
        .mod = pow(z.mod, power),
        .arg = power * z.arg,
        .is_polar = true,
    };
    COMPLEX_PRINCIPAL_ARG(c.arg);

    if(should_be_cartesian) complex_to_cartesian(&c);

    return c;
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