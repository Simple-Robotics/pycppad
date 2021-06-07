/*
 * Copyright 2020 INRIA
 */

#ifndef __pycppad_numpy_hpp__
#define __pycppad_numpy_hpp__

#include "pycppad/fwd.hpp"

#ifndef PY_ARRAY_UNIQUE_SYMBOL
  #define PY_ARRAY_UNIQUE_SYMBOL PYCPPAD_ARRAY_API
#endif

#include <numpy/numpyconfig.h>
#ifdef NPY_1_8_API_VERSION
  #define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#endif

#include <numpy/noprefix.h>
#include <numpy/ufuncobject.h>

#if defined _WIN32 || defined __CYGWIN__
  #define PYCPPAD_GET_PY_ARRAY_TYPE(array) \
    call_PyArray_MinScalarType(array)->type_num
#else
  #define PYCPPAD_GET_PY_ARRAY_TYPE(array) \
    PyArray_MinScalarType(array)->type_num
#endif

namespace pycppad
{
  void import_numpy();
  int PyArray_TypeNum(PyTypeObject * type);
}

#if defined _WIN32 || defined __CYGWIN__
namespace pycppad
{
  bool call_PyArray_Check(PyObject *);

  PyObject* call_PyArray_SimpleNew(int nd, npy_intp * shape, int np_type);

  PyObject* call_PyArray_New(PyTypeObject * py_type_ptr, int nd, npy_intp * shape, int np_type, void * data_ptr, int options);

  int call_PyArray_ObjectType(PyObject *, int);

  PyTypeObject * getPyArrayType();

  PyArray_Descr * call_PyArray_DescrFromType(int typenum);

  void call_PyArray_InitArrFuncs(PyArray_ArrFuncs * funcs);

  int call_PyArray_RegisterDataType(PyArray_Descr * dtype);

  int call_PyArray_RegisterCanCast(PyArray_Descr *descr, int totype, NPY_SCALARKIND scalar);

  PyArray_Descr * call_PyArray_MinScalarType(PyArrayObject *arr);
}
#else
  #define call_PyArray_Check(py_obj) PyArray_Check(py_obj)
  #define call_PyArray_SimpleNew PyArray_SimpleNew
  #define call_PyArray_New(py_type_ptr,nd,shape,np_type,data_ptr,options) \
    PyArray_New(py_type_ptr,nd,shape,np_type,NULL,data_ptr,0,options,NULL)
  #define getPyArrayType() &PyArray_Type
  #define call_PyArray_DescrFromType(typenum) PyArray_DescrFromType(typenum)
  #define call_PyArray_MinScalarType(py_arr) PyArray_MinScalarType(py_arr)
  #define call_PyArray_InitArrFuncs(funcs) PyArray_InitArrFuncs(funcs)
  #define call_PyArray_RegisterDataType(dtype) PyArray_RegisterDataType(dtype)
  #define call_PyArray_RegisterCanCast(descr,totype,scalar) PyArray_RegisterCanCast(descr,totype,scalar)
#endif

#endif // ifndef __pycppad_numpy_hpp__
