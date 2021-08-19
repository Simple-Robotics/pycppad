/*
 * Copyright 2021 INRIA
 */

#ifdef PYCPPAD_BUILD_CPPAD_CODEGEN_BINDINGS
#include "pycppad/codegen/cppadcg-scalar.hpp"
#endif

#include "pycppad/cppad.hpp"
#include "pycppad/cppad-scalar.hpp"


namespace pycppad
{
  
  void enablePyCppAD()
  {
    exposeCppADScalar<PYCPPAD_SCALAR_TYPE>();

#ifdef PYCPPAD_BUILD_CPPAD_CODEGEN_BINDINGS
    codegen::exposeCppADCGScalar<PYCPPAD_SCALAR_TYPE>();
#endif
    
  }
}
