#include "pygameoflife.h"
#include "cpp-lib/gameoflife.h"
#include "pyvec2.h"
#include "pycolor.h"

namespace 
{
    void reprint(const char* msg, PyObject *obj) 
    {
        PyObject* repr = PyObject_Repr(obj);
        PyObject* str = PyUnicode_AsEncodedString(repr, "utf-8", "~E~");
        const char *bytes = PyBytes_AS_STRING(str);

        printf("REPR %s:, %s\n", msg, bytes);

        Py_XDECREF(repr);
        Py_XDECREF(str);
    }

    PyObject* py_clone(PyGameOfLife* self, PyObject* args)
    {
        auto* wrapper = PyGameOfLife::alloc();
        wrapper->data = new GameOfLife(*self->data);
        return (PyObject*)wrapper;
    }

    PyObject* py_generate_board(PyGameOfLife* self, PyObject* args)
    {
        self->data->generate_board();
        Py_RETURN_NONE;
    }

    PyObject* py_count_alive_neighbors(PyGameOfLife* self, PyObject* args)
    {
        int row, col;
        if (!PyArg_ParseTuple(args, "ii", &row, &col))
            return NULL;

        uint8_t ret = self->data->count_alive_neighbors(row, col);
        return PyLong_FromUnsignedLong(ret);
    }

    PyObject* py_count_alive_cells(PyGameOfLife* self, PyObject* args)
    {
        size_t ret = self->data->count_alive_cells();
        return PyLong_FromSize_t(ret);
    }

    PyObject* py_update_board(PyGameOfLife* self, PyObject* args)
    {
        self->data->update_board();
        Py_RETURN_NONE;
    }

    PyObject* py_get_cell(PyGameOfLife* self, PyObject* args)
    {
        int row, col;
        if (!PyArg_ParseTuple(args, "ii", &row, &col))
            return NULL;

        if (self->data->get_cell(row, col)) 
            Py_RETURN_TRUE;
        else 
            Py_RETURN_FALSE;
    }

    PyObject* py_set_cell(PyGameOfLife* self, PyObject* args)
    {
        // NB: ParseTuple does NOT work with `bool`. Python booleans are parsed as `int`s.
        int row = -1, col = -1, ivalue = -1;
        if (!PyArg_ParseTuple(args, "iii", &row, &col, &ivalue))
            return NULL;

        bool value = (ivalue == 1);
        self->data->set_cell(row, col, value);
        Py_RETURN_NONE;
    }

    int PyGameOfLife_init(PyGameOfLife* self, PyObject* args, PyObject* kwds)
    {
        size_t rows, cols;
        if (!PyArg_ParseTuple(args, "nn", &rows, &cols))
            return -1;

        self->data = new GameOfLife(rows, cols);
        return 0;
    }

    void PyGameOfLife_dealloc(PyGameOfLife* self)
    {
        delete self->data;
        self->data = nullptr;
    }

    PyMethodDef PyGameOfLife_methods[] = 
    {
        { "clone", (PyCFunction)py_clone, METH_VARARGS },
        { "generate_board", (PyCFunction)py_generate_board, METH_VARARGS },
        { "count_alive_neighbors", (PyCFunction)py_count_alive_neighbors, METH_VARARGS },
        { "count_alive_cells", (PyCFunction)py_count_alive_cells, METH_VARARGS },
        { "update_board", (PyCFunction)py_update_board, METH_VARARGS },
        { "get_cell", (PyCFunction)py_get_cell, METH_VARARGS },
        { "set_cell", (PyCFunction)py_set_cell, METH_VARARGS },
        { NULL }
    };

    PyTypeObject PyGameOfLifeType = []
    {
        PyTypeObject ret = {
            PyVarObject_HEAD_INIT(NULL, 0)
        };
        ret.tp_name = "PyGameOfLife";
        ret.tp_doc = NULL;
        ret.tp_basicsize = sizeof(PyGameOfLife);
        ret.tp_itemsize = 0;
        ret.tp_methods = PyGameOfLife_methods;
        ret.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
        ret.tp_new = PyType_GenericNew;
        ret.tp_init = (initproc)PyGameOfLife_init;
        ret.tp_dealloc = (destructor)PyGameOfLife_dealloc;
        return ret;
    }();
}

bool PyGameOfLife::init_type()
{
    if (PyType_Ready(&PyGameOfLifeType) < 0)
        return false;

    return true;
}

bool PyGameOfLife::init_ctor(PyObject* module)
{
    Py_INCREF(&PyGameOfLifeType);
    if (PyModule_AddObject(module, "PyGameOfLife", (PyObject *) &PyGameOfLifeType) < 0) 
    {
        Py_DECREF(&PyGameOfLifeType);
        return false;
    }

    return true;
}

bool PyGameOfLife::isinstance(PyObject* object)
{
    return PyObject_IsInstance(object, (PyObject*)&PyGameOfLifeType);
}

PyGameOfLife* PyGameOfLife::alloc()
{
    return (PyGameOfLife*)PyGameOfLifeType.tp_new(&PyGameOfLifeType, nullptr, nullptr);
}
