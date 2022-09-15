import cffi
ffi = cffi.FFI()
ffi.cdef("""
    typedef struct { size_t x; size_t y; } c_vec2_t;
    typedef struct { int r; int g; int b; } c_color_t;
    typedef struct { double real; double imag; } c_complex_t;
    typedef struct { c_color_t* data; size_t size; } c_image_t;
    typedef struct { void* data; } c_gameoflife_t;

    c_vec2_t cmandelbrot_get_vec2_t(size_t x, size_t y);
    c_color_t cmandelbrot_get_color_t(int r, int g, int b);
    c_color_t cmandelbrot_get_complex_t(double real, double imag);

    c_complex_t cmandelbrot_scale(c_vec2_t point, c_vec2_t size);
    size_t cmandelbrot_get_iterations(c_complex_t p, size_t max_iter);
    c_color_t cmandelbrot_get_rgb_smooth(size_t num, size_t max_iter);
    c_color_t cmandelbrot_get_color(c_vec2_t point, c_vec2_t size, size_t max_iter);
    c_image_t cmandelbrot_get_image(c_vec2_t size, size_t max_iter);

    c_gameoflife_t* cgameoflife_alloc(int rows, int cols);
    void cgameoflife_dealloc(c_gameoflife_t* board);
    c_gameoflife_t* cgameoflife_clone(c_gameoflife_t* board);
    void cgameoflife_generate_board(c_gameoflife_t* board);
    uint8_t cgameoflife_count_alive_neighbors(c_gameoflife_t* board, int row, int col);
    size_t cgameoflife_count_alive_cells(c_gameoflife_t* board);
    void cgameoflife_update_board(c_gameoflife_t* board);
    bool cgameoflife_get_cell(c_gameoflife_t* board, int row, int col);
    void cgameoflife_set_cell(c_gameoflife_t* board, int row, int col, bool value);

""")
lib = ffi.dlopen("lib/libcpp-mandelbrot-lib.so")

# help(lib)
# print(ffi.list_types())

class PyVec2:
    def __init__(self, x, y):
        self._obj = lib.cmandelbrot_get_vec2_t(x, y)

    @property
    def x(self):
        return self._obj.x

    @property
    def y(self):
        return self._obj.y

    def __repr__(self):
        return f'<{self._obj.x}, {self._obj.y}>'


class PyMandelbrot:
    def scale(point, size):
        return lib.cmandelbrot_scale(point._obj, size._obj)

    def get_iterations(point, max_iter):
        return lib.cmandelbrot_get_iterations(point, max_iter)

    def get_rgb_smooth(num, max_iter):
        return lib.cmandelbrot_get_rgb_smooth(num, max_iter)

    def get_color(point, size, max_iter):
        return lib.cmandelbrot_get_color(point._obj, size._obj, max_iter)

    def get_image(size, max_iter):
        ptr = lib.cmandelbrot_get_image(size._obj, max_iter)
        out = []
        for i in range(ptr.size):
            out.append(ptr.data[i])
        return out


class PyGameOfLife:
    _obj = None

    def __init__(self, rows, cols):
        p = lib.cgameoflife_alloc(rows, cols)
        if p == ffi.NULL:
            raise MemoryError("Could not allocate person")

        self._obj = ffi.gc(p, lib.cgameoflife_dealloc)

    def clone(self):
        new_obj = PyGameOfLife.__new__(PyGameOfLife)
        new_obj._obj = lib.cgameoflife_clone(self._obj)
        return new_obj

    def generate_board(self):
        lib.cgameoflife_generate_board(self._obj)

    def count_alive_neighbors(self, row, col):
        return lib.cgameoflife_count_alive_neighbors(self._obj, row, col)

    def count_alive_cells(self):
        return lib.cgameoflife_count_alive_cells(self._obj)

    def update_board(self):
        lib.cgameoflife_update_board(self._obj)

    def get_cell(self, row, col):
        return lib.cgameoflife_get_cell(self._obj, row, col)

    def set_cell(self, row, col, value):
        lib.cgameoflife_set_cell(self._obj, row, col, value)
