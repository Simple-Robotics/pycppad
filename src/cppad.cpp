/*
 * Copyright 2021-2024 INRIA
 */

#ifdef PYCPPAD_WITH_CPPAD_CODEGEN_BINDINGS
  #include "pycppad/codegen/cppadcg-scalar.hpp"
#endif

#include "pycppad/cppad.hpp"
#include "pycppad/cppad-scalar.hpp"


// Use explicit template instantiation to build these
// function in different translation unit and avoid consuming
// too much memory on Windows
typedef ::CppAD::AD<double> ADScalar;
extern template void eigenpy::exposeType<ADScalar>();
extern template void eigenpy::exposeType<ADScalar,Eigen::RowMajor>();

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
