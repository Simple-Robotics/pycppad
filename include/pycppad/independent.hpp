/*
 * Copyright 2021 INRIA
 */

#ifndef __pycppad_independent_hpp__
#define __pycppad_independent_hpp__

#include "pycppad/fwd.hpp"
#include <cppad/core/independent/independent.hpp>

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
    
    static void Independent3(const ADVector &x_,
			     const size_t abort_op_index_,
			     const bool record_compare_)
    {
      ADVector& x = const_cast<ADVector&>(x_);
      size_t abort_op_index = abort_op_index_;
      bool record_compare = record_compare_;
      ::CppAD::Independent(x, abort_op_index, record_compare);
      return;
    }

    static void Independent2(const ADVector &x_, const size_t abort_op_index_)
    {
      ADVector& x = const_cast<ADVector&>(x_);
      size_t abort_op_index = abort_op_index_;
      ::CppAD::Independent(x, abort_op_index);
      return;
    }

    static void Independent1(const ADVector &x_)
    {
      ADVector& x = const_cast<ADVector&>(x_);
      ::CppAD::Independent(x);
      return;
    }

    static void expose()
    {
      bp::def("Independent",&::pycppad::IndependentVisitor<ADVector>::Independent3,
	      bp::args("x", "abort_op_index", "record_compare"),
	      "define a variable as Independent."
	      "Parameters:\n"
	      "\tx: variable\n"
	      "\tabort_op_index: operator index at which execution will be aborted (during the recording of operations). The value zero corresponds to not aborting (will not match).\n"
	      "\trecord_compare: should comparison operators be recorded.\n"
	      );
      bp::def("Independent",&::pycppad::IndependentVisitor<ADVector>::Independent2,
	      bp::args("x", "abort_op_index"),
	      "define a variable as Independent."
	      "Parameters:\n"
	      "\tx: variable\n"
	      "\tabort_op_index: operator index at which execution will be aborted (during the recording of operations). The value zero corresponds to not aborting (will not match).\n"
	      );
      
      bp::def("Independent",&::pycppad::IndependentVisitor<ADVector>::Independent1,
	      bp::args("x"),
	      "define a variable as Independent."
	      "Parameters:\n"
	      "\tx: variable\n"
	      );      
    }
  };
}
#endif //#ifndef __pycppad_ad_hpp__
