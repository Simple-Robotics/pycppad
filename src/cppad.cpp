/*
 * Copyright 2020 INRIA
 */

#include "pycppad/cppad.hpp"


namespace pycppad
{
  void enablePyCppAD()
  {
    exposeCppADScalar<double>();
    exposeCppADScalar<float>();
  }
}
