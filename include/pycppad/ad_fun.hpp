/*
 * Copyright 2021 INRIA
 */

#ifndef __pycppad_ad_fun_expose_hpp__
#define __pycppad_ad_fun_expose_hpp__

#include "pycppad/fwd.hpp"
#include <cppad/cppad.hpp>

namespace pycppad
{
  namespace bp = boost::python;
 
  template<typename Scalar>
  class ADFunVisitor
  :  public bp::def_visitor< ADFunVisitor<Scalar> >
  {

    typedef ::CppAD::ADFun<Scalar> ADFun;
  public:
    
    template<class PyClass>
    void visit(PyClass& cl) const
    {
      cl
	.def("swap", &ADFun::swap, bp::args("self", "f"))
	.def("from_json", &ADFun::from_json, bp::args("self", "json"))
	//.def("to_json", &ADFun::to_json, bp::arg("self"))
	;
    }
    
  private:

  public:
    static void expose()
    {
      bp::class_<ADFun, boost::noncopyable>("ADFun",
			"Class used to hold function objects.\n\n",
			bp::init<>())
	.def(ADFunVisitor<Scalar>());

    }
  };
}
#endif //#ifndef __pycppad_ad_expose_hpp__
