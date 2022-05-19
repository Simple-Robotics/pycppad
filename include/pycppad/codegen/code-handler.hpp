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
      typedef Eigen::Ref<VectorCG> RefVectorCG;
      typedef Eigen::Ref<RowVectorCG> RefRowVectorCG;
      typedef ::CppAD::cg::CodeHandler<Scalar> CodeHandler;
      typedef ::CppAD::cg::LanguageC<Scalar> LanguageC;
      typedef ::CppAD::cg::LangCDefaultVariableNameGenerator<Scalar> LangCDefaultVariableNameGenerator;

      
    protected:

      template<typename Vector>
      static void makeVariables(CodeHandler& self, Eigen::Ref<Vector> x)
      {
        Vector x_(x);
        ::CppAD::cg::ArrayView<typename Vector::Scalar> independent_av(x_.data(), x_.size());
        self.makeVariables(independent_av);
        x = x_;
        return;
      }

      template<typename LangType, typename NameGenType>
      static std::string generateCode(CodeHandler& self,
                                      LangType& lang,
                                      RefVectorCG dependent,
                                      NameGenType& nameGen,
                                      const std::string& jobName)
      {
        std::ostringstream oss;
        VectorCG dependent_(dependent);
        ::CppAD::cg::ArrayView<CG> dependent_av(dependent_.data(), dependent_.size());
        dependent = dependent_;
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
               bp::args("self", "variable"),
               "Marks the provided variable as being an independent variable.\n"
               "Parameters:\n"
               "\tvariable: the variables that will become independent variable")
          .def("makeVariable",
               static_cast<void (CodeHandler::*)(ADCG&)>(&CodeHandler::makeVariable),
               bp::args("self", "variable"),
               "Marks the provided variable as being an independent variable.\n"
               "Parameters:\n"
               "\tvariable: the variables that will become independent variable"
               )
          .def("makeVariables",
               &makeVariables<VectorCG>,
               bp::args("self", "variables"),
               "Marks the provided variables as being independent variables.\n"
               "Parameters:\n"
               "\tvariables: the vector of variables that will become independent variables")
          .def("makeVariables",
               &makeVariables<VectorADCG>,
               bp::args("self", "variables"),
               "Marks the provided variables as being independent variables.\n"
               "Parameters:\n"
               "\tvariables: the vector of variables that will become independent variables")
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
          .def("getAtomicFunctionName", &CodeHandler::getAtomicFunctionName, bp::args("self", "id"),
               "Provides the name used by an atomic function with a given ID.\n"
               "Parameters:\n"
               "\tid:  the atomic function ID.")
          //.def("getExternalFuncMaxForwardOrder", &CodeHandler::getExternalFuncMaxForwardOrder, bp::arg("self"))
          //.def("getExternalFuncMaxReverseOrder", &CodeHandler::getExternalFuncMaxReverseOrder, bp::arg("self"))
          .def("generateCode", &generateCode<LanguageC, LangCDefaultVariableNameGenerator>,
               (bp::arg("self"), bp::arg("lang"), bp::arg("dependent"), bp::arg("nameGen"), bp::arg("jobName")="source"),
               "Creates the source code from the operations registered so far.\n"
               "Parameters:\n"
               "\tlang: The targeted language.\n"
               "\tdependent: The dependent variables for which the source code\n"
               "             should be generated. By defining this vector the \n"
               "             number of operations in the source code can be\n"
               "             reduced and thus providing a more optimized code.\n"
               "\tnameGen: Provides the rules for variable name creation. data related to the model\n"
               "\tjobName: Name of this job.")
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
