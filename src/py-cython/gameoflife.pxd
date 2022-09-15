from libc.stdint cimport *

cdef extern from "gameoflife.h":
    cdef cppclass GameOfLife:
        GameOfLife(int rows, int cols) except +
        GameOfLife(GameOfLife& other) except +

        GameOfLife* clone()
        void generate_board()
        uint8_t count_alive_neighbors(int row, int col)
        size_t count_alive_cells()
        void update_board()
        bint get_cell(int row, int col)
        void set_cell(int row, int col, bint value)

