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
    template<class PyClass>
    void visit(PyClass&) const
    { }

  protected:
    
    static std::string & get_class_name()
    {
      static std::string class_name;
      return class_name;
    }
    
    static void set_class_name(const std::string & class_name)
    {
      get_class_name() = class_name;
    }

    
  public:
    
    static void Independent(RefADVector x,
                            const size_t abort_op_index_,
                            const bool record_compare_)
    {
      ADVector x_(x), dynamic(0);
      size_t abort_op_index = abort_op_index_;
      bool record_compare = record_compare_;
      ::CppAD::Independent(x_, abort_op_index, record_compare, dynamic);
      x = x_;
      return;
    }

    static void expose(const std::string & class_name = "Independent")
    {
      set_class_name(class_name);
      bp::def(class_name.c_str(),&Independent,
              (bp::arg("x"), bp::arg("abort_op_index") = 0, bp::arg("record_compare") = true),
              "define a variable as Independent."
              "Parameters:\n"
              "\tx: variable\n"
              "\tabort_op_index: operator index at which execution will be aborted (during the recording of operations). The value zero corresponds to not aborting (will not match).\n"
              "\trecord_compare: should comparison operators be recorded.\n"
              );
    }
  };
}
#endif //#ifndef __pycppad_ad_hpp__
