/*
 * Copyright 2021 INRIA
 */
#ifndef __pycppad_codegen_lang_c_lang_c_default_var_name_gen_hpp__
#define __pycppad_codegen_lang_c_lang_c_default_var_name_gen_hpp__

#include <cppad/cg/lang/c/lang_c_default_var_name_gen.hpp>

namespace pycppad
{
  namespace codegen
  {
    template<typename Scalar>
    class LangCDefaultVariableNameGeneratorVisitor
      : public bp::def_visitor< LangCDefaultVariableNameGeneratorVisitor<Scalar> >
    {
    public:
      
      typedef ::CppAD::cg::LangCDefaultVariableNameGenerator<Scalar> LangCDefaultVariableNameGenerator;
      
      template<class PyClass>
      void visit(PyClass& cl) const
      {
        cl
          .def(bp::init<std::string, std::string, std::string, std::string, std::string>
               (bp::args("self","y","x","v","array","sarray")))
          ;
      }
      
      static void expose(const std::string & class_name = "LangCDefaultVariableNameGenerator")
      {
        bp::class_<LangCDefaultVariableNameGenerator,
                   boost::noncopyable>(class_name.c_str(),
                                       "Creates variables names for the source code",
                                       bp::no_init)
          .def(LangCDefaultVariableNameGeneratorVisitor<Scalar>());
      }
    };

  }
}
#endif //#ifndef __pycppad_codegen_lang_c_lang_c_default_var_name_gen_hpp__
