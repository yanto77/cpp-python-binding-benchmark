#include "pymandelbrot.h"
#include "cpp-lib/mandelbrot.h"
#include "pyvec2.h"
#include "pycolor.h"

namespace 
{
    PyObject* py_scale(PyObject* self, PyObject* args)
    {
        PyObject* point;
        PyObject* size;
        if (!PyArg_ParseTuple(args, "OO", &point, &size))
            return NULL;

        if (!PyVec2::isinstance(point) || !PyVec2::isinstance(size)) 
            return NULL;

        auto ret = Mandelbrot::scale(((PyVec2*)point)->vec, ((PyVec2*)size)->vec);
        return Py_BuildValue("dd", ret.real(), ret.imag());
    }

    PyObject* py_get_iterations(PyObject* self, PyObject* args)
    {
        double real, imag;
        size_t max_iter;
        if (!PyArg_ParseTuple(args, "(dd)n", &real, &imag, &max_iter))
            return NULL;

        size_t ret = Mandelbrot::get_iterations({ real, imag }, max_iter);
        return PyLong_FromSize_t(ret);
    }

    PyObject* py_get_rgb_smooth(PyObject* self, PyObject* args)
    {
        size_t num, max_iter;
        if (!PyArg_ParseTuple(args, "nn", &num, &max_iter))
            return NULL;

        auto* ret = PyColor::alloc();
        ret->color = Mandelbrot::get_rgb_smooth(num, max_iter);
        return (PyObject*)ret;
    }

    PyObject* py_get_color(PyObject* self, PyObject* args)
    {
        PyObject* py_point;
        PyObject* py_size;
        size_t max_iter;
        if (!PyArg_ParseTuple(args, "OOn", &py_point, &py_size, &max_iter))
            return NULL;

        if (!PyVec2::isinstance(py_point) || !PyVec2::isinstance(py_size)) 
            return NULL;

        auto* ret = PyColor::alloc();
        const vec2u point = ((PyVec2*)py_point)->vec;
        const vec2u size = ((PyVec2*)py_size)->vec;
        ret->color = Mandelbrot::get_color(point, size, max_iter);
        return (PyObject*)ret;
    }

    PyObject* py_get_image(PyObject* self, PyObject* args)
    {
        PyObject* py_size;
        size_t max_iter;
        if (!PyArg_ParseTuple(args, "On", &py_size, &max_iter))
            return NULL;

        if (!PyVec2::isinstance(py_size)) 
            return NULL;

        const vec2u size = ((PyVec2*)py_size)->vec;
        std::vector<color_t> result = Mandelbrot::get_image(size, max_iter);

        PyObject* retList = PyList_New(result.size());
        for (size_t i = 0; i < result.size(); i++) 
        {
            auto* ret = PyColor::alloc();
            ret->color = result[i];
            PyList_SET_ITEM(retList, i, (PyObject*)ret);
        }
        return retList;
    }

    PyMethodDef PyMandelbrot_methods[] = 
    {
        { "scale", py_scale, METH_STATIC | METH_VARARGS },
        { "get_iterations", py_get_iterations, METH_STATIC | METH_VARARGS },
        { "get_rgb_smooth", py_get_rgb_smooth, METH_STATIC | METH_VARARGS },
        { "get_color", py_get_color, METH_STATIC | METH_VARARGS },
        { "get_image", py_get_image, METH_STATIC | METH_VARARGS },
        { NULL }
    };

    PyTypeObject PyMandelbrotType = []
    {
        PyTypeObject ret = {
            PyVarObject_HEAD_INIT(NULL, 0)
        };
        ret.tp_name = "PyMandelbrot";
        ret.tp_doc = NULL;
        ret.tp_basicsize = sizeof(PyMandelbrot);
        ret.tp_itemsize = 0;
        ret.tp_methods = PyMandelbrot_methods;
        ret.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
        ret.tp_new = PyType_GenericNew;
        return ret;
    }();
}

bool PyMandelbrot::init_type()
{
    if (PyType_Ready(&PyMandelbrotType) < 0)
        return false;

    return true;
}

bool PyMandelbrot::init_ctor(PyObject* module)
{
    Py_INCREF(&PyMandelbrotType);
    if (PyModule_AddObject(module, "PyMandelbrot", (PyObject *) &PyMandelbrotType) < 0) 
    {
        Py_DECREF(&PyMandelbrotType);
        return false;
    }

    return true;
}

bool PyMandelbrot::isinstance(PyObject* object)
{
    return PyObject_IsInstance(object, (PyObject*)&PyMandelbrotType);
}

PyMandelbrot* PyMandelbrot::alloc()
{
    return (PyMandelbrot*)PyMandelbrotType.tp_new(&PyMandelbrotType, nullptr, nullptr);
}
