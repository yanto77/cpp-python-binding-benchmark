from libcpp.vector cimport vector
from libcpp.complex cimport complex

from mandelbrot cimport vec2u, color_t, Mandelbrot

cdef class PyVec2:
    cdef vec2u c_vec

    def __init__(self, size_t x, size_t y):
        self.c_vec.x = x
        self.c_vec.y = y

    @property
    def x(self):
        return self.c_vec.x

    @property
    def y(self):
        return self.c_vec.y

    def __repr__(self):
        return f'<{self.c_vec.x}, {self.c_vec.y}>'

cdef class PyColor:
    cdef color_t c_color

    def __init__(self, int r, int g, int b):
        self.c_color.r = r
        self.c_color.g = g
        self.c_color.b = b

    @property
    def r(self):
        return self.c_color.r

    @property
    def g(self):
        return self.c_color.g
    
    @property
    def b(self):
        return self.c_color.b
        
    def __repr__(self):
        return f'<{self.c_color.r}, {self.c_color.g}, {self.c_color.b}>'


cdef class PyMandelbrot:
    @staticmethod
    def scale(PyVec2 point, PyVec2 size):
        return Mandelbrot.scale(point.c_vec, size.c_vec)

    @staticmethod
    def get_iterations(complex[double] point, size_t max_iter):
        return Mandelbrot.get_iterations(point, max_iter)

    @staticmethod
    def get_rgb_smooth(size_t num, size_t max_iter):
        c = Mandelbrot.get_rgb_smooth(num, max_iter)
        return PyColor(c.r, c.g, c.b)

    @staticmethod
    def get_color(PyVec2 point, PyVec2 size, size_t max_iter):
        c = Mandelbrot.get_color(point.c_vec, size.c_vec, max_iter)
        return PyColor(c.r, c.g, c.b)

    @staticmethod
    def get_image(PyVec2 size, size_t max_iter):
        vec = Mandelbrot.get_image(size.c_vec, max_iter)
        out = []
        for i in range(vec.size()):
            c = vec[i]
            out.append(PyColor(c.r, c.g, c.b))
        return out