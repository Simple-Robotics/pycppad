/*
 * Copyright 2021 INRIA
 */

#ifndef __pycppad_ad_fun_expose_hpp__
#define __pycppad_ad_fun_expose_hpp__

#include "pycppad/fwd.hpp"
//#include "pycppad/user-type.hpp"
//##include "pycppad/ufunc.hpp"
#include <cppad/cppad.hpp>
//#include <cppad/core/ad.hpp>

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
    }
    
  private:
    
    static std::string print(const AD& self)
    {
      std::stringstream ss;
      ss <<"CppAD(" << self <<")";
      return ss.str();
    }
    
    static Scalar Value(const AD& self)
    {
      return CppAD::Value<Scalar> (self);
    }    


  public:
    static void expose()
    {
      bp::class_<AD>("AD",
		     "AD type corresponding to the scalar.\n\n",
		     bp::init<Scalar>(bp::arg("value")))
	.def(ADVisitor<Scalar>());

      bp::def("Value",&Value,
	      bp::arg("x"),
	      "Conversion from AD to Base type");

      //int code = registerNewType<AD>();
      //std::cout<<"code:"<<code<<std::endl;
      //registerCommonUfunc<AD>();
    }
  };
}
#endif //#ifndef __pycppad_ad_expose_hpp__
