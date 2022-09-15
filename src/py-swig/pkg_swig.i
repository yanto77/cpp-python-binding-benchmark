%module pkg_swig
// Ref: https://github.com/swig/swig/tree/master/Lib/python
%include <std_complex.i>
%include <std_vector.i>
%include <stdint.i>

%{
    #define SWIG_FILE_WITH_INIT
    #include "../cpp-lib/mandelbrot.h"
    #include "../cpp-lib/gameoflife.h"
%}

%include "../cpp-lib/mandelbrot.h"
%include "../cpp-lib/gameoflife.h"

namespace std
{
    %template(ColorVector) vector<color_t>;
}

%extend vec2u {
  vec2u(double x, double y) {
    vec2u* v = (vec2u*)malloc(sizeof(vec2u));
    v->x = x;
    v->y = y;
    return v;
  }
};

%pythoncode %{
  PyMandelbrot = Mandelbrot
  PyVec2 = vec2u
  PyGameOfLife = GameOfLife
%}