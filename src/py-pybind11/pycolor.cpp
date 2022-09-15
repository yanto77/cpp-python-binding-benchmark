#include "cpp-lib/mandelbrot.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_pycolor(py::module_& m)
{
    py::class_<color_t>(m, "PyColor")
        .def(py::init())
        .def_readwrite("r", &color_t::r)
        .def_readwrite("g", &color_t::g)
        .def_readwrite("b", &color_t::b);
}
