/*
 * Copyright 2020 INRIA
 */

#include "pycppad/ad.hpp"
#include "pycppad/independent.hpp"

#include <eigenpy/eigenpy.hpp>
#include <cppad/cppad.hpp>


namespace pycppad
{
  void exposeMatrixFloat()
  {
    typedef float Scalar;
    typedef CppAD::AD<Scalar> ADScalar;
    enum { Options = 0 };
    
    eigenpy::exposeType<ADScalar>();
    eigenpy::exposeType<ADScalar,Eigen::RowMajor>();

    pycppad::ADVisitor<Scalar>::expose();
    pycppad::IndependentVisitor< Eigen::Matrix<ADScalar,Eigen::Dynamic,1,Options> >::expose();
    //pycppad::IndependentVisitor<Eigen::Matrix<ADScalar,Eigen::Dynamic,1,Eigen::RowMajor> >::expose();
    
  }
}
