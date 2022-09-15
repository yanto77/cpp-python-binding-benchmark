#define PY_SSIZE_T_CLEAN
#include "Python.h"
#include "cpp-lib/mandelbrot.h"
#include "pyvec2.h"
#include "pymandelbrot.h"
#include "pycolor.h"
#include "pygameoflife.h"

PyMODINIT_FUNC
PyInit_pkg_manual(void)
{
    static PyMethodDef methods[] = 
    {
        { NULL, NULL, 0, NULL }
    };

    static struct PyModuleDef module = 
    {
        PyModuleDef_HEAD_INIT,
        "pkg_manual",
        nullptr,
        -1,
        methods
    };

    if (!PyMandelbrot::init_type())
        return NULL;
        
    if (!PyVec2::init_type())
        return NULL;

    if (!PyColor::init_type())
        return NULL;

    if (!PyGameOfLife::init_type())
        return NULL;
    
    PyObject* m = PyModule_Create(&module);
    if (m == NULL)
        return NULL;

    if (!PyMandelbrot::init_ctor(m))
    {
        Py_DECREF(m);
        return NULL;
    }
        
    if (!PyVec2::init_ctor(m))
    {
        Py_DECREF(m);
        return NULL;
    }

    if (!PyColor::init_ctor(m))
    {
        Py_DECREF(m);
        return NULL;
    }

    if (!PyGameOfLife::init_ctor(m))
    {
        Py_DECREF(m);
        return NULL;
    }

    return m;
}
