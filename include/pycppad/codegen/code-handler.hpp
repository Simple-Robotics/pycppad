/*
 * Copyright 2021 INRIA
 */
#ifndef __pycppad_codegen_code_handler_hpp__
#define __pycppad_codegen_code_handler_hpp__

#include <cppad/cg/code_handler.hpp>
#include <cppad/cg/lang/c/language_c.hpp>
#include <cppad/cg/lang/c/lang_c_default_var_name_gen.hpp>

namespace pycppad
{
  namespace codegen
  {
    
    namespace bp = boost::python;
    
    template<typename Scalar>
    class CodeHandlerVisitor
      : public bp::def_visitor< CodeHandlerVisitor<Scalar> >
    {
    public:
      typedef ::CppAD::cg::CG<Scalar> CG;
      typedef ::CppAD::AD<CG> ADCG;
      typedef ::CppAD::AD<Scalar> AD;
      typedef Eigen::Matrix<ADCG,Eigen::Dynamic,1> VectorADCG;
      typedef Eigen::Matrix<AD,Eigen::Dynamic,1> VectorAD;
      typedef Eigen::Matrix<ADCG,1,Eigen::Dynamic> RowVectorADCG;
      typedef Eigen::Matrix<CG,Eigen::Dynamic,1> VectorCG;
      typedef Eigen::Matrix<CG,1,Eigen::Dynamic> RowVectorCG;      
      typedef ::CppAD::cg::CodeHandler<Scalar> CodeHandler;
      typedef ::CppAD::cg::LanguageC<Scalar> LanguageC;
      typedef ::CppAD::cg::LangCDefaultVariableNameGenerator<Scalar> LangCDefaultVariableNameGenerator;

      
    protected:
      template<typename VectorType>
      static void makeVariables(CodeHandler& self, const VectorType& x)
      {
        VectorType& x_= const_cast<VectorType&>(x);
        self.makeVariables(x_);
        return;
      }

      template<typename VectorType, typename LangType, typename NameGenType>
      static std::string generateCode(CodeHandler& self,
                                      LangType& lang,
                                      const VectorType& dependent,
                                      NameGenType& nameGen,
                                      const std::string& jobName)
      {
        std::ostringstream oss;
        VectorType& dependent_= const_cast<VectorType&>(dependent);
        ::CppAD::cg::ArrayView<typename VectorType::Scalar> dependent_av(dependent_.data(), dependent_.size());
        self.generateCode(oss, lang, dependent_av, nameGen, jobName);
        return oss.str();
      }

      
    public:
      
      template<class PyClass>
      void visit(PyClass& cl) const
      {
        cl
          .def(bp::init<size_t>(bp::args("self","varCount")))
          .def("setReuseVariableIDs", &CodeHandler::setReuseVariableIDs, bp::args("self", "reuse"))
          .def("isReuseVariableIDs", &CodeHandler::isReuseVariableIDs, bp::arg("self"))
          .def("makeVariable",
               static_cast<void (CodeHandler::*)(CG&)>(&CodeHandler::makeVariable),
               bp::args("self", "variable"), "")
          .def("makeVariable",
               static_cast<void (CodeHandler::*)(ADCG&)>(&CodeHandler::makeVariable),
               bp::args("self", "variable"), "")
          .def("makeVariables",
               &makeVariables<VectorCG>,
               bp::args("self", "variables"), "")
          .def("makeVariables",
               &CodeHandler::template makeVariables<RowVectorADCG>,
               bp::args("self", "variables"), "")
          .def("makeVariables",
               &CodeHandler::template makeVariables<VectorCG>,
               bp::args("self", "variables"), "")
          .def("makeVariables",
               &CodeHandler::template makeVariables<RowVectorCG>,
               bp::args("self", "variables"), "")          
          .def("getIndependentVariableSize", &CodeHandler::getIndependentVariableSize, bp::arg("self"))
          .def("getIndependentVariableIndex", &CodeHandler::getIndependentVariableIndex, bp::args("self", "var"))
          .def("getMaximumVariableID", &CodeHandler::getMaximumVariableID, bp::arg("self"))
          .def("isVerbose", &CodeHandler::isVerbose, bp::arg("self"))
          .def("setVerbose", &CodeHandler::setVerbose, bp::arg("self"))
          //.def("getJobTimer", &CodeHandler::getJobTimer, bp::arg("self"))
          //.def("setJobTimer", &CodeHandler::setJobTimer, bp::args("self", "jobTimer"))
          .def("isZeroDependents", &CodeHandler::isZeroDependents, bp::arg("self"))
          .def("setZeroDependents", &CodeHandler::setZeroDependents, bp::args("self", "zeroDependents"))
          .def("getOperationTreeVisitId", &CodeHandler::getOperationTreeVisitId, bp::arg("self"))
          .def("startNewOperationTreeVisit", &CodeHandler::startNewOperationTreeVisit, bp::arg("self"))
          .def("isVisited", &CodeHandler::isVisited, bp::args("self", "node"))
          .def("markVisited", &CodeHandler::markVisited, bp::args("self", "node"))
          .def("getAtomicFunctionName", &CodeHandler::getAtomicFunctionName, bp::args("self", "id"))
          //.def("getExternalFuncMaxForwardOrder", &CodeHandler::getExternalFuncMaxForwardOrder, bp::arg("self"))
          //.def("getExternalFuncMaxReverseOrder", &CodeHandler::getExternalFuncMaxReverseOrder, bp::arg("self"))
          .def("generateCode", &generateCode<VectorCG, LanguageC, LangCDefaultVariableNameGenerator>,
               bp::args("self", "lang", "dependent", "nameGen", "jobName"))
          .def("generateCode", &generateCode<RowVectorCG, LanguageC, LangCDefaultVariableNameGenerator>,
               bp::args("self", "lang", "dependent", "nameGen", "jobName"))
          ;
      }
      
      static void expose(const std::string & class_name = "CodeHandler")
      {
        bp::class_<CodeHandler,
                   boost::noncopyable>(class_name.c_str(),
                                       "Helper class to analyze the operation graph"
                                       "and generate source code for several languages",
                                       bp::no_init)
          .def(CodeHandlerVisitor<Scalar>());
      }
    };

  }
}
#endif //#ifndef __pycppad_codegen_code_handler_hpp__
