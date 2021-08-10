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
  template<typename Scalar>
  void exposeCppADScalar()
  {
    typedef ::CppAD::AD<Scalar> ADScalar;   
    enum { Options = 0 };
    
    pycppad::ADVisitor<Scalar>::expose();
    pycppad::ADFunVisitor<Scalar>::expose();
    eigenpy::exposeType<ADScalar>();
    eigenpy::exposeType<ADScalar,Eigen::RowMajor>();
    
    EIGENPY_MAKE_TYPEDEFS_ALL_SIZES(ADScalar,Options,ads);

    pycppad::IndependentVisitor<Vector2ads>::expose();
    pycppad::IndependentVisitor<RowVector2ads>::expose();
    pycppad::IndependentVisitor<Matrix2ads>::expose();
    pycppad::IndependentVisitor<Matrix2Xads>::expose();
    pycppad::IndependentVisitor<MatrixX2ads>::expose();
    
    pycppad::IndependentVisitor<Vector3ads>::expose();
    pycppad::IndependentVisitor<RowVector3ads>::expose();
    pycppad::IndependentVisitor<Matrix3ads>::expose();
    pycppad::IndependentVisitor<Matrix3Xads>::expose();
    pycppad::IndependentVisitor<MatrixX3ads>::expose();
    
    pycppad::IndependentVisitor<Vector4ads>::expose();
    pycppad::IndependentVisitor<RowVector4ads>::expose();
    pycppad::IndependentVisitor<Matrix4ads>::expose();
    pycppad::IndependentVisitor<Matrix4Xads>::expose();
    pycppad::IndependentVisitor<MatrixX4ads>::expose();
    
    pycppad::IndependentVisitor<VectorXads>::expose();
    pycppad::IndependentVisitor<RowVectorXads>::expose();
    pycppad::IndependentVisitor<MatrixXads>::expose();

  }
}
