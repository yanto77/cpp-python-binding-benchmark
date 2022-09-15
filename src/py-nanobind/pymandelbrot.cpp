#include "cpp-lib/mandelbrot.h"
#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>
#include "nanobind/complex.h"

namespace nb = nanobind;

void init_pymandelbrot(nb::module_& m)
{
    nb::class_<Mandelbrot>(m, "PyMandelbrot")
        .def(nb::init())
        .def_static("scale", &Mandelbrot::scale)
        .def_static("get_iterations", &Mandelbrot::get_iterations)
        .def_static("get_rgb_smooth", &Mandelbrot::get_rgb_smooth)
        .def_static("get_color", &Mandelbrot::get_color)
        .def_static("get_image", &Mandelbrot::get_image);
}
