#include "cpp-lib/mandelbrot.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>

namespace py = pybind11;

void init_pymandelbrot(py::module_& m)
{
    py::class_<Mandelbrot>(m, "PyMandelbrot")
        .def(py::init())
        .def_static("scale", &Mandelbrot::scale)
        .def_static("get_iterations", &Mandelbrot::get_iterations)
        .def_static("get_rgb_smooth", &Mandelbrot::get_rgb_smooth)
        .def_static("get_color", &Mandelbrot::get_color)
        .def_static("get_image", &Mandelbrot::get_image);
}
