/*
 * Copyright 2024 INRIA
 */

#include "pycppad/cppad.hpp"
#include "pycppad/cppad-scalar.hpp"

typedef ::CppAD::AD<double> ADScalar;
template void eigenpy::exposeType<ADScalar>();
