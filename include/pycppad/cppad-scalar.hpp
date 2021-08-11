/*
 * Copyright 2021 INRIA
 */

#ifndef __pycppad_cppad_scalar_hpp__
#define __pycppad_cppad_scalar_hpp__

#include "pycppad/ad.hpp"
#include "pycppad/independent.hpp"
#include "pycppad/ad_fun.hpp"

#include <eigenpy/eigenpy.hpp>


#define PYCPPAD_MAKE_VECTOR_TYPEDEFS(Type, TypeSuffix, Size, SizeSuffix) \
  /** \ingroup matrixtypedefs */                                    \
  typedef Eigen::Matrix<Type, Size, 1>    Vector##SizeSuffix##TypeSuffix; \
  /** \ingroup matrixtypedefs */                                    \
  typedef Eigen::Matrix<Type, 1, Size>    RowVector##SizeSuffix##TypeSuffix;

#define PYCPPAD_MAKE_VECTOR_TYPEDEFS_ALL_SIZES(Type, TypeSuffix) \
  PYCPPAD_MAKE_VECTOR_TYPEDEFS(Type, TypeSuffix, 2, 2)			 \
  PYCPPAD_MAKE_VECTOR_TYPEDEFS(Type, TypeSuffix, 3, 3) \
  PYCPPAD_MAKE_VECTOR_TYPEDEFS(Type, TypeSuffix, 4, 4) \
  PYCPPAD_MAKE_VECTOR_TYPEDEFS(Type, TypeSuffix, Eigen::Dynamic, X)

namespace pycppad
{
  template<typename Scalar>
  void exposeCppADScalar()
  {
    typedef ::CppAD::AD<Scalar> ADScalar;
    eigenpy::exposeType<ADScalar>();
    eigenpy::exposeType<ADScalar,Eigen::RowMajor>();

    
    pycppad::ADVisitor<Scalar>::expose();
    pycppad::ADFunVisitor<Scalar>::expose();
    
    PYCPPAD_MAKE_VECTOR_TYPEDEFS_ALL_SIZES(ADScalar,ads);

    pycppad::IndependentVisitor<Vector2ads>::expose();
    pycppad::IndependentVisitor<RowVector2ads>::expose();
    pycppad::IndependentVisitor<Vector3ads>::expose();
    pycppad::IndependentVisitor<RowVector3ads>::expose();
    pycppad::IndependentVisitor<Vector4ads>::expose();
    pycppad::IndependentVisitor<RowVector4ads>::expose();
    pycppad::IndependentVisitor<VectorXads>::expose();
    pycppad::IndependentVisitor<RowVectorXads>::expose();
  }
}

#endif // ifndef __pycppad_cppad_scalar_hpp__
