/*
    Modified from pybind11/complex.h and nanobind/stl/string.h
    Copyright (c) 2016 Wenzel Jakob <wenzel.jakob@epfl.ch>
*/
#pragma once
#include <nanobind/nanobind.h>
#include <complex>

NAMESPACE_BEGIN(NB_NAMESPACE)
NAMESPACE_BEGIN(detail)

using T = double;

template <> 
struct type_caster<std::complex<T>> 
{
    NB_TYPE_CASTER(std::complex<T>, const_name("complex"));

    bool from_python(handle src, uint8_t, cleanup_list *) noexcept 
    {
        if (!PyComplex_Check(src.ptr())) {
            return false;
        }

        Py_complex result = PyComplex_AsCComplex(src.ptr());
        if (result.real == -1.0 && PyErr_Occurred()) {
            PyErr_Clear();
            return false;
        }
        value = std::complex<T>((T) result.real, (T) result.imag);
        return true;
    }

    static handle from_cpp(const std::complex<T>& value, rv_policy, cleanup_list *) noexcept 
    {
        return PyComplex_FromDoubles((T) value.real(), (T) value.imag());
    }
};

NAMESPACE_END(detail)
NAMESPACE_END(NB_NAMESPACE)
