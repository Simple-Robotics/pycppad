/*
 * Copyright 2014-2019, CNRS
 * Copyright 2018-2019, INRIA
 */

#ifndef __pycppad_exception_hpp__
#define __pycppad_exception_hpp__

#include <exception>
#include <string>

#include "pycppad/fwd.hpp"

namespace pycppad
{
  /*
   * Pycppad exception. They can be catch with python (equivalent pycppad.exception class).
   */
  class Exception : public std::exception
  {
  public:
    Exception() : message() {}
    Exception(const std::string & msg) : message(msg) {}
    const char *what() const throw()
    {
      return this->getMessage().c_str();
    }
    ~Exception() throw() {}
    virtual const std::string & getMessage() const { return message; }
    std::string copyMessage() const { return getMessage(); }

    /* Call this static function to "enable" the translation of this C++ exception in Python. */
    static void registerException();

  private:
    static void translateException( Exception const & e );
    static PyObject * pyType;
  protected:
    std::string message;
   };

} // namespace pycppad

#endif // ifndef __pycppad_exception_hpp__
