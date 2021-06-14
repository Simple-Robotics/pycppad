/*
 * Copyright 2021 INRIA
 */

#ifndef __pycppad_independent_expose_hpp__
#define __pycppad_independent_expose_hpp__

#include "pycppad/fwd.hpp"
//#include "pycppad/user-type.hpp"
//##include "pycppad/ufunc.hpp"
#include <cppad/core/independent/independent.hpp>
//#include <cppad/core/ad.hpp>

namespace pycppad
{
  namespace bp = boost::python;
 
  template<typename ADVector>
  class IndependentVisitor
  :  public bp::def_visitor< IndependentVisitor<ADVector> >
  {
  public:
    template<class PyClass>
    void visit(PyClass&) const
    { }
    

  public:
    static void expose()
    {
      bp::def<void (*)(ADVector &, size_t, bool)>(
	     "Independent",
	     &::CppAD::Independent<ADVector>,
	     bp::args("x", "abort_op_index", "record_compare"),
	     "define a variable as Independent."
	     "Parameters:\n"
	     "\tx: variable\n"
	     "\tabort_op_index: operator index at which execution will be aborted (during the recording of operations). The value zero corresponds to not aborting (will not match).\n"
	     "\trecord_compare: should comparison operators be recorded.\n"
						  );

      bp::def<void (*)(ADVector &, size_t)>(
	     "Independent",
	     &::CppAD::Independent<ADVector>,
	     bp::args("x", "abort_op_index"),
	     "define a variable as Independent."
	     "Parameters:\n"
	     "\tx: variable\n"
	     "\tabort_op_index: operator index at which execution will be aborted (during the recording of operations). The value zero corresponds to not aborting (will not match).\n"
					    );
      
      bp::def<void (*)(ADVector &)>(
	     "Independent",
	     &::CppAD::Independent<ADVector>,
	     bp::args("x"),
	     "define a variable as Independent."
	     "Parameters:\n"
	     "\tx: variable\n"
						  );
      

      
      //int code = registerNewType<AD>();
      //std::cout<<"code:"<<code<<std::endl;
      //registerCommonUfunc<AD>();
    }
  };
}
#endif //#ifndef __pycppad_ad_expose_hpp__
