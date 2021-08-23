/*
 * Copyright 2021 INRIA
 */
#ifndef __pycppad_codegen_code_handler_hpp__
#define __pycppad_codegen_code_handler_hpp__

#include <cppad/cg/code_handler.hpp>

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
      typedef Eigen::Matrix<ADCG,Eigen::Dynamic,1> VectorADCG;
      typedef Eigen::Matrix<ADCG,1,Eigen::Dynamic> RowVectorADCG;
      
      typedef ::CppAD::cg::CodeHandler<Scalar> CodeHandler;
      
      template<class PyClass>
      void visit(PyClass& cl) const
      {
        cl
          .def(bp::init<size_t>(bp::arg("self"),bp::arg("varCount") = 50))
          .def("setReuseVariableIDs", &CodeHandler::setReuseVariableIDs, bp::args("self", "reuse"))
          .def("isReuseVariableIDs", &CodeHandler::isReuseVariableIDs, bp::arg("self"))
          .def("makeVariable",
               static_cast<void (*)(CG&)>(&CodeHandler::makeVariable),
               bp::args("self", "variable"), "")
          .def("makeVariable",
               static_cast<void (*)(ADCG&)>(&CodeHandler::makeVariable),
               bp::args("self", "variable"), "")
          .def("makeVariables",
               static_cast<void (*)(VectorADCG&)>(&CodeHandler::makeVariable<VectorADCG>),
               bp::args("self", "variables"), "")
          .def("makeVariables",
               static_cast<void (*)(RowVectorADCG&)>(&CodeHandler::makeVariable<RowVectorADCG>),
               bp::args("self", "variables"), "")
          .def("getIndependentVariableSize", &CodeHandler::getIndependentVariableSize, bp::arg("self"))
          .def("getIndependentVariableIndex", &CodeHandler::getIndependentVariableIndex, bp::args("self", "var"))
          .def("getMaximumVariableID", &CodeHandler::getMaximumVariableID, bp::arg("self"))
          .def("isVerbose", &CodeHandler::isVerbose, bp::arg("self"))
          .def("setVerbose", &CodeHandler::setVerbose, bp::arg("self"))
          .def("getJobTimer", &CodeHandler::getJobTimer, bp::arg("self"))
          .def("setJobTimer", &CodeHandler::setJobTimer, bp::args("self", "jobTimer"))
          .def("isZeroDependents", &CodeHandler::isZeroDependents, bp::arg("self"))
          .def("setZeroDependents", &CodeHandler::setZeroDependents, bp::args("self", "zeroDependents"))
          .def("getOperationTreeVisitId", &CodeHandler::getOperationTreeVisitId, bp::arg("self"))
          .def("startOperationTreeVisit", &CodeHandler::startOperationTreeVisit, bp::arg("self"))
          .def("isVisited", &CodeHandler::isVisited, bp::args("self", "node"))
          .def("markVisited", &CodeHandler::markVisited, bp::args("self", "node"))
          .def("getAtomicFunctionName", &CodeHandler::getAtomicFunctionName, bp::args("self", "id"))
          .def("getExternamFuncMaxForwardOrder", &CodeHandler::getExternalFuncMaxForwardOrder, bp::arg("self"))
          .def("getExternalFuncMaxReverseOrder", &CodeHandler::getExternalFuncMaxReverseOrder, bp::arg("self"))
          .def("generateCode", &CodeHandler::generateCode, bp::arg("self", "out", "lang", "dependent", "nameGen", "jobName"))
        .def("__repr__",&print)
        ;
      }

    private:

      static std::string print(const CodeHandler & self)
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
      
      static void expose(const std::string & class_name = "CodeHandler")
      {
        set_class_name(class_name);
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
