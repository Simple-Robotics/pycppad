/*
 * Copyright 2021 INRIA
 */

#ifndef __pycppad_cppad_codegen_scalar_hpp__
#define __pycppad_cppad_codegen_scalar_hpp__

#include <cppad/cg/cppadcg.hpp>
#include <eigenpy/eigenpy.hpp>

#include "pycppad/codegen/cg.hpp"


namespace pycppad
{
  namespace codegen {

    template<typename Scalar>
    void exposeCppADCGScalar()
    {
      typedef ::CppAD::cg::CG<Scalar> CGScalar;
      
      eigenpy::exposeType<CGScalar>();
      eigenpy::exposeType<CGScalar,Eigen::RowMajor>();
      
      CGVisitor<Scalar>::expose();
    }
  }
}

#endif // ifndef __pycppad_cppad_scalar_hpp__
