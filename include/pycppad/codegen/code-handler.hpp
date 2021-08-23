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
      typedef Eigen::Matrix<CG,Eigen::Dynamic,1> VectorCG;
      typedef Eigen::Matrix<CG,1,Eigen::Dynamic> RowVectorCG;      
      typedef ::CppAD::cg::CodeHandler<Scalar> CodeHandler;
      
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
               &CodeHandler::template makeVariables<VectorADCG>,
               bp::args("self", "variables"), "")
          // .def("makeVariables",
          //      &CodeHandler::template makeVariables<RowVectorADCG>,
          //      bp::args("self", "variables"), "")
          // .def("makeVariables",
          //      &CodeHandler::template makeVariables<VectorCG>,
          //      bp::args("self", "variables"), "")
          // .def("makeVariables",
          //      &CodeHandler::template makeVariables<RowVectorCG>,
          //      bp::args("self", "variables"), "")          
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
          //.def("generateCode", &CodeHandler::generateCode,
          //     bp::args("self", "out", "lang", "dependent", "nameGen", "jobName"))
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
