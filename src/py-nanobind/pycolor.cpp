#include "cpp-lib/mandelbrot.h"
#include <nanobind/nanobind.h>

namespace nb = nanobind;

void init_pycolor(nb::module_& m)
{
    nb::class_<color_t>(m, "PyColor")
        .def(nb::init())
        .def_readwrite("r", &color_t::r)
        .def_readwrite("g", &color_t::g)
        .def_readwrite("b", &color_t::b);
}
