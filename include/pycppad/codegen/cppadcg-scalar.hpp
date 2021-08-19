/*
 * Copyright 2021 INRIA
 */

#ifndef __pycppad_cppad_codegen_scalar_hpp__
#define __pycppad_cppad_codegen_scalar_hpp__

#include <cppad/cg/cppadcg.hpp>
#include <eigenpy/eigenpy.hpp>

#include "pycppad/codegen/cg.hpp"
#include "pycppad/codegen/ad.hpp"
#include "pycppad/ad.hpp"
#include "pycppad/ad_fun.hpp"


namespace pycppad
{
  namespace codegen {

    template<typename Scalar>
    void exposeCppADCGScalar()
    {
      typedef ::CppAD::cg::CG<Scalar> CGScalar;
      typedef ::CppAD::AD<CGScalar> ADCGScalar;
      //typedef Eigen::Matrix<ADCGScalar,Eigen::Dynamic,1> VectorADCG;
      //typedef Eigen::Matrix<ADCGScalar,1,Eigen::Dynamic> RowVectorADCG;
      
      eigenpy::exposeType<CGScalar>();
      eigenpy::exposeType<CGScalar,Eigen::RowMajor>();

      eigenpy::exposeType<ADCGScalar>();
      eigenpy::exposeType<ADCGScalar,Eigen::RowMajor>();

      CGVisitor<Scalar>::expose();


      pycppad::ADVisitor<CGScalar>::expose("ADCG");
      //pycppad::ADFunVisitor<CGScalar>::expose("ADCGFun");
      //pycppad::IndependentVisitor<VectorADCG>::expose();
      //pycppad::IndependentVisitor<RowVectorADCG>::expose();      
    }
  }
}

#endif // ifndef __pycppad_cppad_scalar_hpp__
