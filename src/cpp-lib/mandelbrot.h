#pragma once
#include <cstddef>
#include <complex>
#include <vector>

struct vec2u
{
    size_t x;
    size_t y;
};

struct color_t
{
    int r;
    int g;
    int b;
};

class Mandelbrot
{
public:
    static std::complex<double> scale(vec2u point, vec2u size);

    static size_t get_iterations(std::complex<double> p, size_t max_iter);

    static color_t get_rgb_smooth(size_t num, size_t max_iter);

    static color_t get_color(vec2u point, vec2u size, size_t max_iter);

    static std::vector<color_t> get_image(vec2u size, size_t max_iter);
};
