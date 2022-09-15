#pragma once 
#define PY_SSIZE_T_CLEAN
#include "Python.h"

class GameOfLife;

struct PyGameOfLife 
{
    PyObject_HEAD
    GameOfLife* data = nullptr;

    static bool init_type();
    static bool init_ctor(PyObject* module);
    static bool isinstance(PyObject* object);
    static PyGameOfLife* alloc();
};
