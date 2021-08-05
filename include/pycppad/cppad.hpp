/*
 * Copyright 2021, INRIA
 */

#ifndef __pycppad_cppad_hpp__
#define __pycppad_cppad_hpp__


namespace pycppad
{

  // void exposeMatrixBool();
  // void exposeMatrixInt();
  // void exposeMatrixLong();
  void exposeMatrixFloat();
  void exposeMatrixDouble();
  // void exposeMatrixLongDouble();

  // void exposeMatrixComplexFloat();
  //void exposeMatrixComplexDouble();
  // void exposeMatrixComplexLongDouble();

  void enablePyCppAD();
}

#endif  // #ifndef __pycppad_cppad_hpp__
