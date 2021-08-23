/*
 * Copyright 2021 INRIA
 */
#ifndef __pycppad_codegen_lang_c_language_c_hpp__
#define __pycppad_codegen_lang_c_language_c_hpp__

#include <cppad/cg/lang/c/language_c.hpp>

namespace pycppad
{
  namespace codegen
  {
    template<typename Scalar>
    class LanguageCVisitor
      : public bp::def_visitor< LanguageCVisitor<Scalar> >
    {
    public:
      
      typedef ::CppAD::cg::LanguageC<Scalar> LanguageC;
      
      template<class PyClass>
      void visit(PyClass& cl) const
      {
        cl
          .def(bp::init<std::string, size_t>(bp::args("self","varTypeName","spaces")))
          ;
      }

    public:
      
      static void expose(const std::string & class_name = "LanguageC")
      {
        bp::class_<LanguageC,
                   boost::noncopyable>(class_name.c_str(),
                                       "C language source code generator",
                                       bp::no_init)
          .def(LanguageCVisitor<Scalar>());
      }
    };

  }
}
#endif //#ifndef __pycppad_codegen_lang_c_language_c_hpp__
