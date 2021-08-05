/*
 * Copyright 2020 INRIA
 */

#include <eigenpy/eigenpy.hpp>
#include <cppad/cppad.hpp>
#include "pycppad/cppad.hpp"


namespace pycppad
{
  void enablePyCppAD()
  {    
    exposeMatrixDouble();    
    exposeMatrixFloat(); 
  }
}
