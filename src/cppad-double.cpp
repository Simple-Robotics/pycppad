/*
 * Copyright 2020 INRIA
 */

#include "pycppad/ad.hpp"
#include "pycppad/independent.hpp"
#include "pycppad/ad_fun.hpp"

#include <eigenpy/eigenpy.hpp>
#include <cppad/cppad.hpp>

namespace pycppad
{
  void exposeMatrixDouble()
  {
    typedef double Scalar;
    typedef ::CppAD::AD<Scalar> ADScalar;
    enum { Options = 0 };
    
    eigenpy::exposeType<ADScalar>();
    eigenpy::exposeType<ADScalar,Eigen::RowMajor>();
    pycppad::ADVisitor<Scalar>::expose();
    pycppad::IndependentVisitor<Eigen::Matrix<ADScalar,Eigen::Dynamic,1,Options> >::expose();
    pycppad::IndependentVisitor<Eigen::Matrix<ADScalar,2,1,Options> >::expose();
    pycppad::ADFunVisitor<ADScalar>::expose();
    //pycppad::IndependentVisitor<Eigen::Matrix<ADScalar,Eigen::Dynamic,1,Eigen::RowMajor> >::expose();
    
    
  }
}
