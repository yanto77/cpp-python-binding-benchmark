#include "cpp-lib/mandelbrot.h"
#include <nanobind/nanobind.h>

namespace nb = nanobind;

void init_pyvec2(nb::module_& m)
{
    nb::class_<vec2u>(m, "PyVec2")
        .def(nb::init<size_t, size_t>())
        .def_readwrite("x", &vec2u::x)
        .def_readwrite("y", &vec2u::y);
}
