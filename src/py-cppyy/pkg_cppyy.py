import cppyy
cppyy.include('lib/include/mandelbrot.h')
cppyy.include('lib/include/gameoflife.h')
cppyy.load_library('lib/libcpp-mandelbrot-lib.so')

PyMandelbrot = cppyy.gbl.Mandelbrot
PyVec2 = cppyy.gbl.vec2u
PyGameOfLife = cppyy.gbl.GameOfLife