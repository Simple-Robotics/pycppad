/*
 * Copyright 2020 INRIA
 */

#include <eigenpy/eigenpy.hpp>
#include <cppad/cppad.hpp>

namespace pycppad
{
  void exposeMatrixDouble()
  {
    typedef double Scalar;
    typedef CppAD::AD<Scalar> ADScalar;

    eigenpy::exposeType<ADScalar>();
    eigenpy::exposeType<ADScalar,Eigen::RowMajor>();
  }
}
