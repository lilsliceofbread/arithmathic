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


int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        ARITH_LOG(LOG_ERROR, "please provide a filename as an argument\n");
        return -1;
    }
    const char* filename = argv[1];

    Complex c = {
        .re = -0.8696,
        .im = 0.26,
        .is_polar = false,
    };
    const u32 width = 1920, height = 1080, components = 3;
    const f64 aspect = (f64)1920 / (f64)1080;

    const u32 iters = 20;
    const f64 max_mod = 3.0;
    const f64 zoom = 2.0;

    u8* img = (u8*)malloc(width * height * components);

    for(u32 y = 0; y < height; y++)
    {
        for(u32 x = 0; x < width; x++)
        {
            f64 x_pos = (f64)x / (f64)width;
            f64 y_pos = (f64)y / (f64)height;
            Complex z = {
                .re = zoom * (x_pos - 0.5) * aspect,
                .im = zoom * (0.5 - (y_pos)),
                .is_polar = false,
            };

            for(u32 i = 0; i < iters; i++)
            {
                z = complex_pow(z, 2);
                z = complex_add(z, c);
            }

            u8 val = 0xFF;
            if(complex_modulus(z) < max_mod) val = 0x00;

            u32 index = (y * width * components) + (x * components);
            img[index] = val;
            img[index + 1] = val;
            img[index + 2] = val;
        }
    }

    stbi_write_png(filename, (i32)width, (i32)height, (i32)components, (void*)img, (i32)(width * components));
    ARITH_LOG_NO_CTX(LOG_INFO, "Image %s generated in working directory\n", filename);

    free(img);
    return 0;
}