#include "mandelbrot.h"

std::complex<double> Mandelbrot::scale(vec2u point, vec2u size)
{
    double sx0 = -2.0, sx1 = 0.47, sy0 = -1.12, sy1 = 1.12;

    double scaled_x = point.x / (double)size.x * (sx1 - sx0) + sx0;
    double scaled_y = point.y / (double)size.y * (sy1 - sy0) + sy0;
    return std::complex<double>(scaled_x, scaled_y);
}

size_t Mandelbrot::get_iterations(std::complex<double> p, size_t max_iter)
{
    std::complex<double> z(0, 0);

    size_t i = 0;
    while (abs(z) < 2 && i <= max_iter) 
    {
        z = z * z + p;
        i++;
    }

    return (i < max_iter) ? i : 0;
}

// Ref: https://solarianprogrammer.com/2013/02/28/mandelbrot-set-cpp-11/
color_t Mandelbrot::get_rgb_smooth(size_t num, size_t max)
{
    // map n on the 0..1 interval
    double t = (double)num/(double)max;
    
    // Use smooth polynomials for r, g, b
    int r = (int)(9*(1-t)*t*t*t*255);
    int g = (int)(15*(1-t)*(1-t)*t*t*255);
    int b =  (int)(8.5*(1-t)*(1-t)*(1-t)*t*255);
    return color_t{r, g, b};
}

color_t Mandelbrot::get_color(vec2u point, vec2u size, size_t max_iter)
{
    std::complex<double> sp = scale(point, size);
    size_t iter = get_iterations(sp, max_iter);
    return get_rgb_smooth(iter, max_iter);
}

std::vector<color_t> Mandelbrot::get_image(vec2u size, size_t max_iter)
{
    std::vector<color_t> out;

    for (size_t i = 0; i < size.x; i++) 
    {
        for (size_t j = 0; j < size.y; j++)  
        {
            color_t c = Mandelbrot::get_color({ i, j }, size, max_iter);
            out.push_back(c);
        }
    }

    return out;
}
