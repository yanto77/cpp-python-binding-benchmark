#pragma once 
#define PY_SSIZE_T_CLEAN
#include "Python.h"
#include "cpp-lib/mandelbrot.h"

struct PyVec2 
{
    PyObject_HEAD
    vec2u vec;

    static bool init_type();
    static bool init_ctor(PyObject* module);
    static bool isinstance(PyObject* object);
    static PyVec2* alloc();
};
