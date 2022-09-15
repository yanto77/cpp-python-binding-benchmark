#pragma once 
#include "stddef.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    size_t x;
    size_t y;
} c_vec2_t;

c_vec2_t cmandelbrot_get_vec2_t(size_t x, size_t y);

typedef struct
{
    int r;
    int g;
    int b;
} c_color_t;

c_color_t cmandelbrot_get_color_t(int r, int g, int b);

typedef struct
{
    double real;
    double imag;
} c_complex_t;

c_complex_t cmandelbrot_get_complex_t(double real, double imag);

typedef struct
{
    c_color_t* data;
    size_t size;
} c_image_t;

c_complex_t cmandelbrot_scale(c_vec2_t point, c_vec2_t size);
size_t cmandelbrot_get_iterations(c_complex_t p, size_t max_iter);
c_color_t cmandelbrot_get_rgb_smooth(size_t num, size_t max_iter);
c_color_t cmandelbrot_get_color(c_vec2_t point, c_vec2_t size, size_t max_iter);
c_image_t cmandelbrot_get_image(c_vec2_t size, size_t max_iter);

#ifdef __cplusplus
}
#endif