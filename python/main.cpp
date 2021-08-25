/*
 * Copyright 2021 INRIA
 */

#include <Eigen/Core>
#include <eigenpy/eigenpy.hpp>

#include "pycppad/cppad.hpp"
#include "pycppad/ad.hpp"
#include "pycppad/independent.hpp"

#include <sstream>

inline std::string printVersion(const std::string & delimiter = ".")
{
  std::ostringstream oss;
  oss
  << PYCPPAD_MAJOR_VERSION << delimiter
  << PYCPPAD_MINOR_VERSION << delimiter
  << PYCPPAD_PATCH_VERSION;
  return oss.str();
}

namespace bp = boost::python;

BOOST_PYTHON_MODULE(pycppad_pywrap)
{
  bp::docstring_options module_docstring_options(true,true,false);
  
  bp::scope().attr("__version__") = printVersion();
  bp::scope().attr("__raw_version__") = bp::str(PYCPPAD_VERSION);
  
  eigenpy::enableEigenPy();
  pycppad::enablePyCppAD();
}
