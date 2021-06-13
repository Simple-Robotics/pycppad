/*
 * Copyright 2021 INRIA
 */

#ifndef __pycppad_ad_expose_hpp__
#define __pycppad_ad_expose_hpp__

#include "pycppad/fwd.hpp"
#include <cppad/cppad.hpp>
#include <cppad/core/ad.hpp>

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
	.def(bp::self *= bp::self);
    }
    
    static void expose()
    {
      bp::class_<AD>("AD",
		     "AD type corresponding the scalar (typically double).\n\n",
		     bp::init<Scalar>(bp::arg("value")))
	.def(ADVisitor<Scalar>());
    }
  };
}
#endif //#ifndef __pycppad_ad_expose_hpp__
