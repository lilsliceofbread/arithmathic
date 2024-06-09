#include <stdio.h>
#include "defines.h"

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

#define BACKGROUND_COLOUR 255 
#define FOREGROUND_COLOUR 0 

#define IMG_COMPONENTS 3

void generate_arbelos_image(const char* filename, u32 width, u32 height, f64 r1, f64 r2);

int main(int argc, char* argv[])
{
    if(argc != 6)
    {
        ARITH_LOG_NO_CTX(LOG_ERROR, "please provide arguments in the form\n ./executable [filename] [image width] [image height] [radius of semicircle 1] [radius of semicircle 2]\n");
        return -1;
    }

    const char* filename = argv[1];
    const u32 width = (u32)atoi(argv[2]);
    const u32 height = (u32)atoi(argv[3]);

    f64 r1 = atof(argv[4]);
    f64 r2 = atof(argv[5]);

    if(filename == NULL || width == 0 || height == 0)
    {
        ARITH_LOG_NO_CTX(LOG_ERROR, "Missing or 0 argument\n");
        return -1;
    }

    if(r1 < 0 || r2 < 0)
    {
        ARITH_LOG_NO_CTX(LOG_ERROR, "radius must be 0 or greater\n");
        return -1;
    }


    generate_arbelos_image(filename, width, height, r1, r2);
    ARITH_LOG_NO_CTX(LOG_INFO, "Image %s generated in working directory\n", filename);

    return 0;
}

void generate_arbelos_image(const char* filename, u32 width, u32 height, f64 r1, f64 r2)
{
    const f64 aspect = (f64)width / (f64)height;
    const f64 zoom = (1.5 * (r1 + r2));

    u8* img = (u8*)malloc(width * height * IMG_COMPONENTS);
    memset(img, BACKGROUND_COLOUR, width * height * IMG_COMPONENTS); // set all memory to background colour automatically

    for(u32 y = 0; y < height; y++)
    {
        f64 y_pos = ((f64)y + 0.5) / height; // position from top left
        f64 y_cartesian = 0.5 - y_pos;
        y_cartesian = zoom * y_cartesian + (0.5f * (r1 + r2)); // zoom out and shift viewport to frame arbelos better
        
        // this ensures semicircles are drawn, since all the diameters are on the same line
        if(y_cartesian <= 0.0)  // ! real end of for loop (can't do this in for loop check)
            break;

        for(u32 x = 0; x < width; x++)
        {
            f64 x_pos = ((f64)x + 0.5) / width; // position from top left

            f64 x_cartesian = (x_pos - 0.5) * aspect;
            x_cartesian = zoom * x_cartesian; // zoom out

            /* semicircle positions:
             * big: 0, 0
             * small 1: r1 - (r1 + r2) = -r2, 0
             * small 2: (r1 + r2) - r2 = r1, 0
             */

            u8 shade = FOREGROUND_COLOUR;

            // repeats calculations but idc
            // if within 2 smaller semicircles then background pixel
            f64 dist_to_semicircle1 = sqrt(SQUARED_DIST(x_cartesian, y_cartesian, -r2, 0.0));
            f64 dist_to_semicircle2 = sqrt(SQUARED_DIST(x_cartesian, y_cartesian, r1, 0.0));
            if(dist_to_semicircle1 <= r1 || dist_to_semicircle2 <= r2)
                shade = BACKGROUND_COLOUR;

            // if outside of big semicircle then background pixel
            f64 dist_to_big = sqrt(SQUARED_DIST(x_cartesian, y_cartesian, 0.0, 0.0));
            if(dist_to_big > (r1 + r2))
                shade = BACKGROUND_COLOUR;
        
            u32 index = (y * width * IMG_COMPONENTS) + (x * IMG_COMPONENTS);
            img[index] = shade;
            img[index + 1] = shade;
            img[index + 2] = shade;
        }
    }

    char filename_with_extension[1024];
    sprintf(filename_with_extension, "%s.png", filename);
    stbi_write_png(filename_with_extension, (i32)width, (i32)height, (i32)IMG_COMPONENTS, (void*)img, (i32)(width * IMG_COMPONENTS));

    free(img);
}