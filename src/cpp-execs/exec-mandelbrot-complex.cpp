#include "cpp-lib/mandelbrot.h"
#include "config.h"
#include "helpers.h"

int main()
{
    const vec2u size = { MANDELBROT_SIZE_X, MANDELBROT_SIZE_Y };
    std::vector<color_t> pixels;

    {
        stack_timer_t t("mandelbrot, complex, cpp");
        for (size_t i = 0; i < MANDELBROT_SIZE_X; i++) 
        {
            for (size_t j = 0; j < MANDELBROT_SIZE_Y; j++)  
            {
                std::complex<double> sp = Mandelbrot::scale({ i, j }, size);
                size_t iter = Mandelbrot::get_iterations(sp, MANDELBROT_MAX_ITER);
                color_t c = Mandelbrot::get_rgb_smooth(iter, MANDELBROT_MAX_ITER);
                pixels.push_back(c);
            }
        }
    }

    write_ppm("out-cpp-complex.ppm", size, pixels);
    return EXIT_SUCCESS;
}
