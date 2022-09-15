#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_pyvec2(py::module_& m);
void init_pycolor(py::module_& m);
void init_pymandelbrot(py::module_& m);
void init_pygameoflife(py::module_& m);

PYBIND11_MODULE(pkg_pybind11, m)
{
    init_pyvec2(m);
    init_pycolor(m);
    init_pymandelbrot(m);
    init_pygameoflife(m);
}
