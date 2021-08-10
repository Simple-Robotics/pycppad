/*
 * Copyright 2021 INRIA
 */

#include "pycppad/cppad.hpp"
#include "pycppad/cppad-scalar.hpp"


namespace pycppad
{
  void enablePyCppAD()
  {
    exposeCppADScalar<double>();
    exposeCppADScalar<float>();
  }
}
