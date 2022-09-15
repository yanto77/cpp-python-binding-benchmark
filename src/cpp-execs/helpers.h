#pragma once
#include "cpp-lib/mandelbrot.h"
#include <fstream>
#include <vector>
#include <chrono>

void write_ppm(const char* fname, vec2u size, const std::vector<color_t>& pixels)
{
    std::ofstream img(fname);
    if (!img.is_open()) 
    {
        printf("ERROR: Could not open the file\n");
        return;
    }

    img << "P3\n" << size.x << " " << size.y << " 255\n";
    for (color_t p: pixels)
    {
        img << p.r << ' ' << p.g << ' ' << p.b << "\n";
    }
    img.close();
}

class stack_timer_t
{
    typedef std::chrono::steady_clock clock_t;

    public:
        stack_timer_t(const char* _msg)
            : t0(clock_t::now()), msg(_msg)
        {
        }

        ~stack_timer_t()
        {
            auto elapsed = (clock_t::now() - t0);
            double time = ((double)elapsed.count() / (1000.0 * 1000.0 * 1000.0));
            printf("%s, %0.3f sec\n", msg, time);
        }

    private:
        std::chrono::time_point<clock_t> t0;
        const char* msg;
};
