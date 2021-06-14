/*
 * Copyright 2021 INRIA
 */

#ifndef __pycppad_ad_expose_hpp__
#define __pycppad_ad_expose_hpp__

#include "pycppad/fwd.hpp"
#include "eigenpy/user-type.hpp"
#include "eigenpy/ufunc.hpp"
#include <cppad/cppad.hpp>
//#include <cppad/core/ad.hpp>

namespace pycppad
{
  
  namespace bp = boost::python;
 
  template<typename Scalar>
  class ADVisitor
  :  public bp::def_visitor< ADVisitor<Scalar> >
  {
    typedef ::CppAD::AD<Scalar> AD;
  public:
    
    template<class PyClass>
    void visit(PyClass& cl) const
    {
      cl
	.def(bp::init<>())
	.def(bp::self + bp::self)
	.def(bp::self - bp::self)
	.def(bp::self * bp::self)
	.def(bp::self / bp::self)
	.def(bp::self += bp::self)
#ifdef __clang__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wself-assign-overloaded"
#endif
	.def(bp::self /= bp::self)
	.def(bp::self -= bp::self) // See https://bugs.llvm.org/show_bug.cgi?id=43124 for the bug
#ifdef __clang__
#pragma GCC diagnostic pop
#endif
	.def(bp::self *= bp::self)
	.def("abs_me", &AD::abs_me, bp::arg("self"))
	.def("acos_me", &AD::acos_me, bp::arg("self"))
	.def("asin_me", &AD::asin_me, bp::arg("self"))
	.def("atan_me", &AD::atan_me, bp::arg("self")) 
	.def("cos_me", &AD::cos_me, bp::arg("self"))
	.def("cosh_me", &AD::cosh_me, bp::arg("self"))
	.def("exp_me", &AD::exp_me, bp::arg("self"))
	.def("fabs_me", &AD::fabs_me, bp::arg("self"))
	.def("log_me", &AD::log_me, bp::arg("self"))
	.def("sin_me", &AD::sin_me, bp::arg("self"))
	.def("sign_me", &AD::sign_me, bp::arg("self"))
	.def("sinh_me", &AD::sinh_me, bp::arg("self"))
	.def("sqrt_me", &AD::sqrt_me, bp::arg("self"))
	.def("tan_me", &AD::tan_me, bp::arg("self"))
	.def("tanh_me", &AD::tanh_me, bp::arg("self"))
	.def("asinh_me", &AD::asinh_me, bp::arg("self"))
	.def("acosh_me", &AD::acosh_me, bp::arg("self"))
	.def("atanh_me", &AD::atanh_me, bp::arg("self"))
	.def("erf_me", &AD::erf_me, bp::args("self", "complement"), "self, bool")
	.def("expm1_me", &AD::expm1_me, bp::arg("self"))
	.def("log1p_me", &AD::log1p_me, bp::arg("self"))
	.def("__str__",&print)
	.def("__repr__",&print)
	;
    }
    
  private:
    
    static std::string print(const AD& self)
    {
      std::stringstream ss;
      ss <<"CppAD(" << self <<")";
      return ss.str();
    }


  public:
    static void expose()
    {
      bp::class_<AD>("AD",
		     "AD type corresponding to the scalar.\n\n",
		     bp::init<Scalar>(bp::arg("value")))
	.def(ADVisitor<Scalar>());

      bp::def("Value",&::CppAD::Value<Scalar>,
	      bp::arg("x"),
	      "Conversion from AD to Base type");

      eigenpy::registerNewType<AD>();
      eigenpy::registerCommonUfunc<AD>();
    }
  };
}
#endif //#ifndef __pycppad_ad_expose_hpp__
