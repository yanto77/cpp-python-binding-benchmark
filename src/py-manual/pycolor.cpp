#include "pycolor.h"
#include "structmember.h"

namespace 
{
    PyMemberDef PyColor_members[] = 
    {
        {"r", T_INT, offsetof(PyColor, color) + offsetof(color_t, r), 0, NULL},
        {"g", T_INT, offsetof(PyColor, color) + offsetof(color_t, g), 0, NULL},
        {"b", T_INT, offsetof(PyColor, color) + offsetof(color_t, b), 0, NULL},
        {NULL}  /* Sentinel */
    };

    static int PyColor_init(PyColor* self, PyObject* args, PyObject* kwds)
    {
        color_t& c = self->color;
        if (!PyArg_ParseTuple(args, "nnn", &c.r, &c.g, &c.b))
            return -1;

        return 0;
    };

    PyTypeObject PyColorType = []
    {
        PyTypeObject ret = {
            PyVarObject_HEAD_INIT(NULL, 0)
        };
        ret.tp_name = "PyColor";
        ret.tp_doc = NULL;
        ret.tp_basicsize = sizeof(PyColor);
        ret.tp_itemsize = 0;
        ret.tp_members = PyColor_members;
        ret.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
        ret.tp_new = PyType_GenericNew;
        ret.tp_init = (initproc)PyColor_init;
        return ret;
    }();
}

bool PyColor::init_type()
{
    if (PyType_Ready(&PyColorType) < 0)
        return false;

    return true;
}

bool PyColor::init_ctor(PyObject* module)
{
    Py_INCREF(&PyColorType);
    if (PyModule_AddObject(module, "PyColor", (PyObject* ) &PyColorType) < 0) 
    {
        Py_DECREF(&PyColorType);
        return false;
    }

    return true;
}

bool PyColor::isinstance(PyObject* object)
{
    return PyObject_IsInstance(object, (PyObject*)&PyColorType);
}

PyColor* PyColor::alloc()
{
    return (PyColor*)PyColorType.tp_new(&PyColorType, nullptr, nullptr);
}
