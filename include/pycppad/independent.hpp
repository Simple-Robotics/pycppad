/*
 * Copyright 2021 INRIA
 */

#ifndef __pycppad_independent_hpp__
#define __pycppad_independent_hpp__

#include "pycppad/fwd.hpp"

#include <eigenpy/eigenpy.hpp>
#include <cppad/core/independent/independent.hpp>

namespace pycppad
{
  namespace bp = boost::python;
 
  template<typename ADVector>
  class IndependentVisitor
  : public bp::def_visitor< IndependentVisitor<ADVector> >
  {
    typedef Eigen::Ref<ADVector> RefADVector;

  public:
    
    static void Independent(RefADVector x,
                            const size_t abort_op_index_,
                            const bool record_compare_)
    {
      ADVector x_(x), dynamic(0);
      ::CppAD::Independent(x_, abort_op_index_, record_compare_, dynamic);
      x = x_;
    }

    static void expose(const std::string & func_name = "Independent")
    {
      bp::def(func_name.c_str(),&Independent,
              (bp::arg("x"), bp::arg("abort_op_index") = 0, bp::arg("record_compare") = true),
              "Define a variable as Independent."
              "Parameters:\n"
              "\tx: variable\n"
              "\tabort_op_index: operator index at which execution will be aborted (during the recording of operations). The value zero corresponds to not aborting (will not match).\n"
              "\trecord_compare: should comparison operators be recorded.\n"
              );
    }
  };
}
#endif //#ifndef __pycppad_ad_hpp__
