#include "pyvec2.h"
#include "structmember.h"

namespace 
{
    PyMemberDef PyVec2_members[] = 
    {
        {"x", T_INT, offsetof(PyVec2, vec) + offsetof(vec2u, x), 0, NULL},
        {"y", T_INT, offsetof(PyVec2, vec) + offsetof(vec2u, y), 0, NULL},
        {NULL}  /* Sentinel */
    };

    static int PyVec2_init(PyVec2* self, PyObject* args, PyObject* kwds)
    {
        vec2u& v = self->vec;
        if (!PyArg_ParseTuple(args, "nn", &v.x, &v.y))
            return -1;

        return 0;
    };

    PyTypeObject PyVec2Type = []
    {
        PyTypeObject ret = {
            PyVarObject_HEAD_INIT(NULL, 0)
        };
        ret.tp_name = "PyVec2";
        ret.tp_doc = NULL;
        ret.tp_basicsize = sizeof(PyVec2);
        ret.tp_itemsize = 0;
        ret.tp_members = PyVec2_members;
        ret.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
        ret.tp_new = PyType_GenericNew;
        ret.tp_init = (initproc)PyVec2_init;
        return ret;
    }();
}

bool PyVec2::init_type()
{
    if (PyType_Ready(&PyVec2Type) < 0)
        return false;

    return true;
}

bool PyVec2::init_ctor(PyObject* module)
{
    Py_INCREF(&PyVec2Type);
    if (PyModule_AddObject(module, "PyVec2", (PyObject *) &PyVec2Type) < 0) 
    {
        Py_DECREF(&PyVec2Type);
        return false;
    }

    return true;
}

bool PyVec2::isinstance(PyObject* object)
{
    return PyObject_IsInstance(object, (PyObject*)&PyVec2Type);
}

PyVec2* PyVec2::alloc()
{
    return (PyVec2*)PyVec2Type.tp_new(&PyVec2Type, nullptr, nullptr);
}
