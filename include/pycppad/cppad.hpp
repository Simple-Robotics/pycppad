/*
 * Copyright 2021, INRIA
 */

#ifndef __pycppad_cppad_hpp__
#define __pycppad_cppad_hpp__

#include "pycppad/fwd.hpp"

namespace pycppad
{

  template<typename Scalar>
  void exposeCppADScalar();

  PYCPPAD_DLLAPI void enablePyCppAD();
}

#endif  // #ifndef __pycppad_cppad_hpp__
