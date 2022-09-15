#include "cpp-lib/gameoflife.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_pygameoflife(py::module_& m)
{
    py::class_<GameOfLife>(m, "PyGameOfLife")
        .def(py::init<int, int>())
        .def("clone", [](const GameOfLife& self) { return GameOfLife(self); })
        .def("generate_board", &GameOfLife::generate_board)
        .def("count_alive_neighbors", &GameOfLife::count_alive_neighbors)
        .def("count_alive_cells", &GameOfLife::count_alive_cells)
        .def("update_board", &GameOfLife::update_board)
        .def("get_cell", &GameOfLife::get_cell)
        .def("set_cell", &GameOfLife::set_cell);
}
