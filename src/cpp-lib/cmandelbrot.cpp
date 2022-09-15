#include "cmandelbrot.h"
#include "mandelbrot.h"

namespace
{
    vec2u to_cpp(c_vec2_t v) 
    { 
        return vec2u { v.x, v.y }; 
    }

    c_vec2_t to_c(vec2u v) 
    { 
        return c_vec2_t { v.x, v.y }; 
    }

    std::complex<double> to_cpp(c_complex_t v) 
    { 
        return std::complex<double>(v.real, v.imag); 
    }

    c_complex_t to_c(std::complex<double> v) 
    { 
        return c_complex_t { v.real(), v.imag() }; 
    }

    c_color_t to_c(color_t c) 
    { 
        return c_color_t { c.r, c.g, c.b }; 
    }
}

c_vec2_t cmandelbrot_get_vec2_t(size_t x, size_t y)
{
    return c_vec2_t { x, y };
}

c_color_t cmandelbrot_get_color_t(int r, int g, int b)
{
    return c_color_t { r, g, b };
}

c_complex_t cmandelbrot_get_complex_t(double real, double imag)
{
    return c_complex_t { real, imag };
}

c_complex_t cmandelbrot_scale(c_vec2_t point, c_vec2_t size)
{
    return to_c(Mandelbrot::scale(to_cpp(point), to_cpp(size)));
}

size_t cmandelbrot_get_iterations(c_complex_t p, size_t max_iter)
{
    return Mandelbrot::get_iterations(to_cpp(p), max_iter);
}

c_color_t cmandelbrot_get_rgb_smooth(size_t num, size_t max_iter)
{
    return to_c(Mandelbrot::get_rgb_smooth(num, max_iter));
}

c_color_t cmandelbrot_get_color(c_vec2_t point, c_vec2_t size, size_t max_iter)
{
    return to_c(Mandelbrot::get_color(to_cpp(point), to_cpp(size), max_iter));
}

c_image_t cmandelbrot_get_image(c_vec2_t size, size_t max_iter)
{
    c_image_t out;
    out.size = size.x * size.y;
    out.data = (c_color_t*)malloc(sizeof(c_color_t) * out.size);

    for (size_t i = 0; i < size.x; i++) 
    {
        for (size_t j = 0; j < size.y; j++)  
        {
            color_t c = Mandelbrot::get_color({ i, j }, to_cpp(size), max_iter);
            out.data[i * size.x + j] = to_c(c);
        }
    }

    return out;
}