from libcpp.vector cimport vector
from libcpp.complex cimport complex

cdef extern from "mandelbrot.h":
   cdef cppclass vec2u:
     size_t x
     size_t y

   cdef cppclass color_t:
     int r
     int g
     int b

   cdef cppclass Mandelbrot:
      @staticmethod
      complex[double] scale(vec2u point, vec2u size)

      @staticmethod
      size_t get_iterations(complex[double] p, size_t max_iter)

      @staticmethod
      color_t get_rgb_smooth(size_t num, size_t max_iter)

      @staticmethod
      color_t get_color(vec2u point, vec2u size, size_t max_iter)

      @staticmethod
      vector[color_t] get_image(vec2u size, size_t max_iter)
