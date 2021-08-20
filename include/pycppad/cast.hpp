/*
 * Copyright 2021 INRIA
 */

#ifndef __pycppad_cast_hpp__
#define __pycppad_cast_hpp__

#include "pycppad/fwd.hpp"

namespace pycppad
{
  namespace internal
  {
  
    template<typename From, typename To>
    struct Cast
    {
      static To run(const From & from)
      {
        return static_cast<To>(from);
      }
    };
  
    template<typename Scalar>
    struct CppADValue
    {
      static Scalar get(const ::CppAD::AD<Scalar> & v)
      {
        return ::CppAD::Value<Scalar>(v);
      }
    };
  
    template<typename Scalar, typename To>
    struct Cast<::CppAD::AD<Scalar>,To>
    {
      typedef ::CppAD::AD<Scalar> From;
      static To run(const From & from)
      {
        return static_cast<To>(CppADValue<Scalar>::get(from));
      }
    };
  } // namespace internal
} // namespace pycppad

#endif //#ifndef __pycppad_cast_hpp__
