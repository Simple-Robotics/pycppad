/*
 * Copyright 2021 INRIA
 */

#ifndef __pycppad_fwd_hpp__
#define __pycppad_fwd_hpp__


#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include <boost/python.hpp>
#include <boost/python/scope.hpp>

#define NO_IMPORT_ARRAY
  #include "pycppad/numpy.hpp"
#undef NO_IMPORT_ARRAY

#undef BOOST_BIND_GLOBAL_PLACEHOLDERS

#endif // ifndef __pycppad_fwd_hpp__
