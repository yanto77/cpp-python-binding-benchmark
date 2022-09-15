#include "cpp-lib/mandelbrot.h"
#include "config.h"
#include "helpers.h"

int main()
{
    const vec2u size = { MANDELBROT_SIZE_X, MANDELBROT_SIZE_Y };
    std::vector<color_t> pixels;

    {
        stack_timer_t t("mandelbrot, simple, cpp");
        for (size_t i = 0; i < MANDELBROT_SIZE_X; i++) 
        {
            for (size_t j = 0; j < MANDELBROT_SIZE_Y; j++)  
            {
                color_t c = Mandelbrot::get_color({ i, j }, size, MANDELBROT_MAX_ITER);
                pixels.push_back(c);
            }
        }
    }

    write_ppm("out-cpp-simple.ppm", size, pixels);
    return EXIT_SUCCESS;
}
