#include "cpp-lib/mandelbrot.h"
#include "config.h"
#include "helpers.h"

int main()
{
    const vec2u size = { MANDELBROT_SIZE_X, MANDELBROT_SIZE_Y };
    std::vector<color_t> pixels;
    
    {
        stack_timer_t t("mandelbrot, single, cpp");
        pixels = Mandelbrot::get_image(size, MANDELBROT_MAX_ITER);
    } 

    write_ppm("out-cpp-single.ppm", size, pixels);
    return EXIT_SUCCESS;
}
