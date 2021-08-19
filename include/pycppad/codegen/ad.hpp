/*
 * Copyright 2021 INRIA
 */

#ifndef __pycppad_codegen_ad_hpp__
#define __pycppad_codegen_ad_hpp__

#include "pycppad/ad.hpp"

namespace pycppad
{
 
  template<>
  int64_t ADVisitor<::CppAD::cg::CG<PYCPPAD_SCALAR_TYPE> >::__int__(const AD & self)
  {
    return static_cast<int>(::CppAD::Value<Scalar>(self).getValue());
  }
}

#endif //#ifndef __pycppad_ad_hpp__
