#pragma once 
#define PY_SSIZE_T_CLEAN
#include "Python.h"

struct PyMandelbrot 
{
    PyObject_HEAD

    static bool init_type();
    static bool init_ctor(PyObject* module);
    static bool isinstance(PyObject* object);
    static PyMandelbrot* alloc();
};
