/*
 * Copyright 2021-2022 INRIA
 */

#ifndef __pycppad_cast_hpp__
#define __pycppad_cast_hpp__

#include "pycppad/fwd.hpp"

#include <eigenpy/user-type.hpp>

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

namespace eigenpy {

template <typename Scalar, typename To>
struct cast<::CppAD::AD<Scalar>, To>
{
  typedef ::CppAD::AD<Scalar> From;
  static To run(const From & from) {
    return ::pycppad::internal::Cast<From, To>::run(from);
  }
};

template <typename From, typename Scalar>
struct cast<From,::CppAD::AD<Scalar>>
{
  typedef ::CppAD::AD<Scalar> To;
  static To run(const From & from) {
    return To(static_cast<Scalar>(from));
  }
};

} // namespace eigenpy

#endif //#ifndef __pycppad_cast_hpp__
