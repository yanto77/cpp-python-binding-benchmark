#pragma once 
#define PY_SSIZE_T_CLEAN
#include "Python.h"
#include "cpp-lib/mandelbrot.h"

struct PyColor 
{
    PyObject_HEAD
    color_t color;

    static bool init_type();
    static bool init_ctor(PyObject* module);
    static bool isinstance(PyObject* object);
    static PyColor* alloc();
};
