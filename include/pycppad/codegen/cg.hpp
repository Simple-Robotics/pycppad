/*
 * Copyright 2021 INRIA
 */

#ifndef __pycppad_codegen_cg_hpp__
#define __pycppad_codegen_cg_hpp__

#include <cppad/cg/cppadcg.hpp>

#include <eigenpy/user-type.hpp>
#include <eigenpy/ufunc.hpp>

#include "pycppad/cast.hpp"

namespace pycppad
{
  namespace internal
  {
  
    template<typename Scalar>
    struct CppADValue<::CppAD::cg::CG<Scalar>>
    {
      static const Scalar & get(const ::CppAD::AD<::CppAD::cg::CG<Scalar>> & v)
      {
        return ::CppAD::Value<::CppAD::cg::CG<Scalar>>(v).getValue();
      }
    };
  
    template<typename Scalar, typename To>
    struct Cast<::CppAD::cg::CG<Scalar>,To>
    {
      typedef ::CppAD::cg::CG<Scalar> From;
      static To run(const From & from)
      {
        return static_cast<To>(::CppAD::Value<From>(from).getValue());
      }
    };
  }

  namespace codegen
  {
    
    namespace bp = boost::python;
    
    template<typename Scalar>
    class CGVisitor
    : public bp::def_visitor< CGVisitor<Scalar> >
    {
    public:
      typedef ::CppAD::cg::CG<Scalar> CG;
      
      template<class PyClass>
      void visit(PyClass& cl) const
      {
        cl
        .def(bp::init<>(bp::arg("self"),"Default constructor"))
        .def(bp::init<Scalar>(bp::args("self","value"),
                              std::string("Constructor from a ").append(bp::type_id<Scalar>().name()).c_str()))
        .def(bp::init<CG>(bp::args("self","other"),"Copy constructor"))
        .def("isIdenticalZero", &CG::isIdenticalZero, bp::arg("self"))
        .def("isIdenticalOne", &CG::isIdenticalOne, bp::arg("self"))
        .def("isValueDefined", &CG::isValueDefined, bp::arg("self"))
        .def("isParameter", &CG::isParameter, bp::arg("self"))
        .def("isVariable", &CG::isVariable, bp::arg("self"))
        
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
        .add_property("value",
                      bp::make_function(&CG::getValue,
                                        bp::return_value_policy<bp::copy_const_reference>()),
                      &CG::setValue)
        .def("__str__",&print)
        .def("__repr__",&print)
        .add_property("__float__",
                      bp::make_function(&CG::getValue,
                                        bp::return_value_policy<bp::copy_const_reference>()),
                      &CG::setValue)
        .def("__int__",&internal::Cast<CG,int64_t>::run)
        ;
      }

    private:

      static std::string print(const CG & self)
      {
        std::stringstream ss;
        ss << get_class_name() << "(" << self <<")";
        return ss.str();
      }
      
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
      
      static void expose(const std::string & class_name = "CG")
      {
        set_class_name(class_name);
        bp::class_<CG>(class_name.c_str(),
                       std::string("CG type corresponding to the scalar type ").append(bp::type_id<Scalar>().name()).c_str(),
                       bp::no_init)
        .def(CGVisitor<Scalar>());
        
        eigenpy::registerNewType<CG>();
        eigenpy::registerCommonUfunc<CG>();
      }
    };

  }
}
#endif //#ifndef __pycppad_codegen_cg_hpp__
