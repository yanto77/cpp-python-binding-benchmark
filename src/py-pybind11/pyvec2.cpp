#include "cpp-lib/mandelbrot.h"
#include <pybind11/pybind11.h>
namespace py = pybind11;

void init_pyvec2(py::module_& m)
{
    py::class_<vec2u>(m, "PyVec2")
        .def(py::init<size_t, size_t>())
        .def_readwrite("x", &vec2u::x)
        .def_readwrite("y", &vec2u::y);
}
