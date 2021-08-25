/*
 * Copyright 2021 INRIA
 */

#ifdef PYCPPAD_WITH_CPPAD_CODEGEN_BINDINGS
  #include "pycppad/codegen/cppadcg-scalar.hpp"
#endif

#include "pycppad/cppad.hpp"
#include "pycppad/cppad-scalar.hpp"

namespace pycppad
{
  
  void enablePyCppAD()
  {
    exposeCppADScalar<double>();

#ifdef PYCPPAD_WITH_CPPAD_CODEGEN_BINDINGS
    codegen::exposeCppADCGScalar<double>();
#endif
    
  }
}
