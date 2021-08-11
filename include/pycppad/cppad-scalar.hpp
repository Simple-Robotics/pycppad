/*
 * Copyright 2021 INRIA
 */

#ifndef __pycppad_cppad_scalar_hpp__
#define __pycppad_cppad_scalar_hpp__

#include "pycppad/ad.hpp"
#include "pycppad/independent.hpp"
#include "pycppad/ad_fun.hpp"

#include <eigenpy/eigenpy.hpp>

namespace pycppad
{
  template<typename Scalar>
  void exposeCppADScalar()
  {
    typedef ::CppAD::AD<Scalar> ADScalar;
    typedef Eigen::Matrix<ADScalar,Eigen::Dynamic,1> VectorAD;
    typedef Eigen::Matrix<ADScalar,1,Eigen::Dynamic> RowVectorAD;
    
    eigenpy::exposeType<ADScalar>();
    eigenpy::exposeType<ADScalar,Eigen::RowMajor>();

    pycppad::ADVisitor<Scalar>::expose();
    pycppad::ADFunVisitor<Scalar>::expose();

    pycppad::IndependentVisitor<VectorAD>::expose();
    pycppad::IndependentVisitor<RowVectorAD>::expose();
  }
}

#endif // ifndef __pycppad_cppad_scalar_hpp__
