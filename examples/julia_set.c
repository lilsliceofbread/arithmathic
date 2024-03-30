#include <stdio.h>
#include "defines.h"
#include "complex.h"
#ifndef _MSC_VER
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wsign-conversion"
    #pragma GCC diagnostic ignored "-Wconversion"
#endif

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#ifndef _MSC_VER
    #pragma GCC diagnostic pop
#endif

#define IMG_COMPONENTS 3

void generate_julia_image(const char* filename, u32 width, u32 height, f64 zoom, Complex c);

int main(int argc, char* argv[])
{
    if(argc != 7)
    {
        ARITH_LOG_NO_CTX(LOG_ERROR, "please provide arguments in the form\n ./executable [filename] [width] [height] [zoom] [c real part] [c imaginary part] ");
        return -1;
    }

    const char* filename = argv[1];
    const u32 width = (u32)atoi(argv[2]);
    const u32 height = (u32)atoi(argv[3]);
    const f64 zoom = atof(argv[4]);

    Complex c = {
        .re = atof(argv[5]),
        .im = atof(argv[6]),
        .is_polar = false,
    };

    if(filename == NULL || width == 0 || height == 0 || zoom == 0.0)
    {
        ARITH_LOG_NO_CTX(LOG_ERROR, "Missing or 0 argument\n");
        return -1;
    }

    generate_julia_image(filename, width, height, zoom, c);
    ARITH_LOG_NO_CTX(LOG_INFO, "Image %s generated in working directory\n", filename);

    return 0;
}

void generate_julia_image(const char* filename, u32 width, u32 height, f64 zoom, Complex c)
{
    const u32 iters = 50;
    const f64 max_mod = 2.0;
    const f64 aspect = (f64)width / (f64)height;

    u8* img = (u8*)malloc(width * height * IMG_COMPONENTS);

    f64 inv_width = 1.0 / (f64)width;
    f64 inv_height = 1.0 / (f64)height;
    for(u32 y = 0; y < height; y++)
    {
        f64 y_pos = ((f64)y + 0.5) * inv_height;

        for(u32 x = 0; x < width; x++)
        {
            f64 x_pos = ((f64)x + 0.5) * inv_width;

            Complex z = { // calculate z from pixel position
                .re = zoom * (x_pos - 0.5) * aspect,
                .im = zoom * (0.5 - y_pos),
                .is_polar = false,
            };

            for(u32 i = 0; i < iters; i++) // iterating julia set
            {
                z = complex_pow(z, 2);
                z = complex_add(z, c);
            }

            u8 val = 0xFF;
            if(complex_modulus(z) < max_mod) val = 0x00; // pixel is black if less than max. modulus after iters

            u32 index = (y * width * IMG_COMPONENTS) + (x * IMG_COMPONENTS);
            img[index] = val;
            img[index + 1] = val;
            img[index + 2] = val;
        }
    }

    stbi_write_png(filename, (i32)width, (i32)height, (i32)IMG_COMPONENTS, (void*)img, (i32)(width * IMG_COMPONENTS));

    free(img);
}