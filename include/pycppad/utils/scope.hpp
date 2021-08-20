//
// Copyright (c) 2019-2021 INRIA
//

#ifndef __pycppad_utils_scope_hpp__
#define __pycppad_utils_scope_hpp__

#include <boost/python.hpp>

namespace pycppad
{

  ///
  /// \brief Helper to create or simply return an existing namespace in Python
  ///
  /// \param[in] submodule_name name of the submodule
  ///
  /// \returns The submodule related to the namespace name.
  ///
  inline boost::python::scope scope(const std::string & submodule_name)
  {
    namespace bp = boost::python;

    bp::scope current_scope;
    std::string current_scope_name(bp::extract<const char*>(current_scope.attr("__name__")));
    std::string complete_submodule_name = current_scope_name + "." + submodule_name;

    bp::object submodule(bp::borrowed(PyImport_AddModule(complete_submodule_name.c_str())));
    current_scope.attr(submodule_name.c_str()) = submodule;

    return submodule;
  }

} // namespace pycppad

#endif // ifndef __pycppad_utils_scope_hpp__
