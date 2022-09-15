#include "cpp-lib/gameoflife.h"
#include <nanobind/nanobind.h>

namespace nb = nanobind;

void init_pygameoflife(nb::module_& m)
{
    nb::class_<GameOfLife>(m, "PyGameOfLife")
        .def(nb::init<int, int>())
        .def("clone", [](const GameOfLife& self) { return GameOfLife(self); })
        .def("generate_board", &GameOfLife::generate_board)
        .def("count_alive_neighbors", &GameOfLife::count_alive_neighbors)
        .def("count_alive_cells", &GameOfLife::count_alive_cells)
        .def("update_board", &GameOfLife::update_board)
        .def("get_cell", &GameOfLife::get_cell)
        .def("set_cell", &GameOfLife::set_cell);
}
