/*
 * Copyright 2021 INRIA
 */

#ifndef __pycppad_ad_expose_hpp__
#define __pycppad_ad_expose_hpp__

#include "pycppad/fwd.hpp"
#include <cppad/core/ad.hpp>

namespace pycppad
{
  
  namespace bp = boost::python;
 
  template<typename Scalar>
  class ADVisitor
    :  public bp::def_visitor< ADVisitor<Scalar> >
  {
    typedef CppAD::AD<Scalar> AD;
  pyblic:
    
    template<class PyClass>
    void visit(PyClass& cl) const
    {
      cl
	.def(bp::self + bp::self)
	.def(bp::self - bp::self)
	.def(bp::self * bp::self)
	.def(bp::self / bp::self)
	.def(bp::self += bp::self)
	.def(bp::self -= bp::self)
	.def(bp::self *= bp::self)
	.def(bp::self /= bp::self);
    }
    
    static void expose()
    {
      bp::class_<Scalar>("AD",
			 "AD type corresponding to Quaternion representing rotation.\n\n"
                             "Supported operations "
                             "('q is a Quaternion, 'v' is a Vector3): "
                             "'q*q' (rotation composition), "
                             "'q*=q', "
                             "'q*v' (rotating 'v' by 'q'), "
                             "'q==q', 'q!=q', 'q[0..3]'.",
			 bp::init<Scalar>(bp::arg("value")))
	.def(ADVisitor<Scalar>());
    }
  };
  
