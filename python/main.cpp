/*
 * Copyright 2021 INRIA
 */

#include <Eigen/Core>
#include <eigenpy/eigenpy.hpp>

#include "pycppad/cppad.hpp"
#include "pycppad/ad.hpp"
#include "pycppad/independent.hpp"


BOOST_PYTHON_MODULE(pycppad)
{
  namespace bp = boost::python;

  //typedef double Scalar;
  //typedef CppAD::AD<Scalar> ADScalar;
  enum { Options = 0 };
  
  eigenpy::enableEigenPy();
  
  //namespace bp = boost::python;
  //bp::scope().attr("__version__") = eigenpy::printVersion();
  //bp::scope().attr("__raw_version__") = bp::str(EIGENPY_VERSION);

  //bp::def("checkVersionAtLeast",&eigenpy::checkVersionAtLeast,
  //        bp::args("major_version","minor_version","patch_version"),
  //        "Checks if the current version of EigenPy is at least the version provided by the input arguments.");

  
  pycppad::enablePyCppAD();

  
  

};
