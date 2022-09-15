from gameoflife cimport GameOfLife

cdef class PyGameOfLife:
    cdef GameOfLife* _ptr

    def __cinit__(self, int rows, int cols):
        self._ptr = new GameOfLife(rows, cols)

    def __dealloc__(self):
        del self._ptr

    def clone(self):
        copy = <PyGameOfLife>PyGameOfLife.__new__(PyGameOfLife, 0, 0)
        del copy._ptr
        copy._ptr = self._ptr.clone()
        return copy

    def generate_board(self):
        self._ptr.generate_board()

    def count_alive_neighbors(self, row, col):
        return self._ptr.count_alive_neighbors(row, col)

    def count_alive_cells(self):
        return self._ptr.count_alive_cells()

    def update_board(self):
        self._ptr.update_board()

    def get_cell(self, row, col):
        return self._ptr.get_cell(row, col)

    def set_cell(self, row, col, value):
        self._ptr.set_cell(row, col, value)
