#include <stdio.h>
#include "defines.h"
#include "matrix.h"
#include "complex.h"

int main(void)
{
    Complex z = {
        .re = 1,
        .im = 1,
        .is_polar = true,
    };

    complex_print(z);

    Complex c = complex_pow(z, 5);
    complex_print(c);

    return 0;
}