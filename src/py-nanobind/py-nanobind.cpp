#include <nanobind/nanobind.h>

namespace nb = nanobind;

void init_pyvec2(nb::module_& m);
void init_pycolor(nb::module_& m);
void init_pymandelbrot(nb::module_& m);
void init_pygameoflife(nb::module_& m);

NB_MODULE(pkg_nanobind, m)
{
    init_pyvec2(m);
    init_pycolor(m);
    init_pymandelbrot(m);
    init_pygameoflife(m);
}
