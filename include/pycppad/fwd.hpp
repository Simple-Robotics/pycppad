/*
 * Copyright 2021 INRIA
 */

#ifndef __pycppad_fwd_hpp__
#define __pycppad_fwd_hpp__

#include "pycppad/config.hpp"
#include "pycppad/deprecated.hpp"
#include "pycppad/warning.hpp"

#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include <boost/python.hpp>
#include <boost/python/scope.hpp>

#undef BOOST_BIND_GLOBAL_PLACEHOLDERS

#include <cppad/cppad.hpp>
#include <Eigen/Core>

#ifndef PYCPPAD_EXCLUDE_EIGEN_NUMTRAITS_SPECIALIZATION

namespace Eigen
{
  template <class Base> struct NumTraits< CppAD::AD<Base> >
  {  // type that corresponds to the real part of an AD<Base> value
    typedef CppAD::AD<Base>   Real;
    // type for AD<Base> operations that result in non-integer values
    typedef CppAD::AD<Base>   NonInteger;
    //  type to use for numeric literals such as "2" or "0.5".
    typedef CppAD::AD<Base>   Literal;
    // type for nested value inside an AD<Base> expression tree
    typedef CppAD::AD<Base>   Nested;
    
    enum {
      // does not support complex Base types
      IsComplex             = 0 ,
      // does not support integer Base types
      IsInteger             = 0 ,
      // only support signed Base types
      IsSigned              = 1 ,
      // must initialize an AD<Base> object
      RequireInitialization = 1 ,
      // computational cost of the corresponding operations
      ReadCost              = 1 ,
      AddCost               = 2 ,
      MulCost               = 2
    };
    
    // machine epsilon with type of real part of x
    // (use assumption that Base is not complex)
    static CppAD::AD<Base> epsilon(void)
    {  return CppAD::numeric_limits< CppAD::AD<Base> >::epsilon(); }
    
    // relaxed version of machine epsilon for comparison of different
    // operations that should result in the same value
    static CppAD::AD<Base> dummy_precision(void)
    {  return 100. *
      CppAD::numeric_limits< CppAD::AD<Base> >::epsilon();
    }
    
    // minimum normalized positive value
    static CppAD::AD<Base> lowest(void)
    {  return CppAD::numeric_limits< CppAD::AD<Base> >::min(); }
    
    // maximum finite value
    static CppAD::AD<Base> highest(void)
    {  return CppAD::numeric_limits< CppAD::AD<Base> >::max(); }
    
    // number of decimal digits that can be represented without change.
    static int digits10(void)
    {  return CppAD::numeric_limits< CppAD::AD<Base> >::digits10; }
  };
} // namespace Eigen

#endif // ifndef PYCPPAD_EXCLUDE_EIGEN_NUMTRAITS_SPECIALIZATION

#endif // ifndef __pycppad_fwd_hpp__
