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
    typedef Eigen::Matrix<::CppAD::AD<Scalar>, Eigen::Dynamic, 1> ADVector;
    typedef Eigen::Matrix<Scalar, Eigen::Dynamic, 1> Vector;
  public:
    
    template<class PyClass>
    void visit(PyClass& cl) const
    {
      cl
	.def("swap", &ADFun::swap, bp::args("self", "f"))
	.def("from_json", &ADFun::from_json, bp::args("self", "json"))
	.def("from_graph", &ADFun::from_graph, bp::args("self", "graph_obj"))
	.def("to_json", &ADFun::to_json, bp::arg("self"))
	.def("Dependent", (void (ADFun::*)(const ADVector &, const ADVector &))(&ADFun::Dependent),
	     bp::args("self", "x", "y"))
	.def("Forward", (Vector (ADFun::*)(size_t , size_t, const Vector&))(&ADFun::Forward),
	     bp::args("self", "q", "r", "x"))
	.def("Forward", (Vector (ADFun::*)(size_t, const Vector&))(&ADFun::Forward),
	     bp::args("self", "q", "xq"))
	.def("Reverse", (Vector (ADFun::*)(size_t, const Vector&))(&ADFun::Reverse),
	     bp::args("self", "p", "v"))
	.def("Reverse", (Vector (ADFun::*)(size_t, const Vector&))(&ADFun::Reverse),
	     bp::args("self", "p", "v"))
	.def("Hessian", (Vector (ADFun::*)(const Vector&,const Vector&))(&ADFun::Hessian),
	     bp::args("self", "x", "w"))
	.def("Hessian", (Vector (ADFun::*)(const Vector&, size_t))(&ADFun::Hessian),
	     bp::args("self", "x", "i"))
	.def("Jacobian", (Vector (ADFun::*)(const Vector&))(&ADFun::Jacobian),
	     bp::args("self", "x"))
	.def("optimize", &ADFun::optimize, bp::args("self", "options"))
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
