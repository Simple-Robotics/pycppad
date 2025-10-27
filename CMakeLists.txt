#
# Copyright (c) 2021-2023 INRIA
#

CMAKE_MINIMUM_REQUIRED(VERSION 3.22)

SET(PROJECT_NAME pycppad)
SET(PROJECT_DESCRIPTION "Python bindings for CppAD and CppADCodeGen using Boost.Python")
SET(PROJECT_URL "https://github.com/simple-robotics/pycppad")
SET(PROJECT_CUSTOM_HEADER_EXTENSION "hpp")
SET(PROJECT_USE_CMAKE_EXPORT TRUE)
# To enable jrl-cmakemodules compatibility with workspace we must define the two
# following lines
SET(PROJECT_AUTO_RUN_FINALIZE FALSE)
SET(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR})


# Project configuration
SET(PROJECT_USE_CMAKE_EXPORT TRUE)
SET(CMAKE_VERBOSE_MAKEFILE TRUE)
SET(CXX_DISABLE_WERROR TRUE)

# Check if the submodule cmake have been initialized
if(EXISTS "${JRL_CMAKE_MODULES}/base.cmake")
  message(STATUS "JRL cmakemodules found in 'cmake/' git submodule")
else()
  find_package(jrl-cmakemodules QUIET CONFIG)
  if(jrl-cmakemodules_FOUND)
    get_property(
      JRL_CMAKE_MODULES
      TARGET jrl-cmakemodules::jrl-cmakemodules
      PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
    message(STATUS "JRL cmakemodules found on system at ${JRL_CMAKE_MODULES}")
  else()
    message(STATUS "JRL cmakemodules not found. Let's fetch it.")
    include(FetchContent)
    FetchContent_Declare("jrl-cmakemodules"
                         GIT_REPOSITORY "https://github.com/jrl-umi3218/jrl-cmakemodules.git")
    FetchContent_MakeAvailable("jrl-cmakemodules")
    FetchContent_GetProperties("jrl-cmakemodules" SOURCE_DIR JRL_CMAKE_MODULES)
  endif()
endif()

# Use BoostConfig module distributed by boost library instead of using FindBoost module distributed
# by CMake
if(POLICY CMP0167)
  cmake_policy(SET CMP0167 NEW)
endif()
INCLUDE(${JRL_CMAKE_MODULES}/base.cmake)
INCLUDE(${JRL_CMAKE_MODULES}/boost.cmake)
INCLUDE(${JRL_CMAKE_MODULES}/ide.cmake)
INCLUDE(${JRL_CMAKE_MODULES}/python.cmake)

# Project definition
COMPUTE_PROJECT_ARGS(PROJECT_ARGS LANGUAGES CXX)
PROJECT(${PROJECT_NAME} ${PROJECT_ARGS})
CHECK_MINIMAL_CXX_STANDARD(11 ENFORCE)

# Project options
OPTION(SUFFIX_SO_VERSION "Suffix library name with its version" ON)
OPTION(BUILD_WITH_CPPAD_CODEGEN_BINDINGS "Build the python bindings for code generation (via CppADCodeGen)" OFF)

SET_BOOST_DEFAULT_OPTIONS()
ADD_PROJECT_DEPENDENCY(Boost REQUIRED)
EXPORT_BOOST_DEFAULT_OPTIONS()

IF(BUILD_WITH_CPPAD_CODEGEN_BINDINGS)
  ADD_PROJECT_DEPENDENCY(cppadcg 2.4.1 REQUIRED PKG_CONFIG_REQUIRES "cppadcg >= 2.4.1" FIND_EXTERNAL "CppAD") # CppADCodeGen 2.4.1 is the first version to check the minimal version of CppAD
  ADD_DEFINITIONS(-DPYCPPAD_WITH_CPPAD_CODEGEN_BINDINGS)
ENDIF(BUILD_WITH_CPPAD_CODEGEN_BINDINGS)

ADD_PROJECT_DEPENDENCY(cppad 20180000.0 REQUIRED PKG_CONFIG_REQUIRES "cppad >= 20180000.0" FIND_EXTERNAL "CppAD")
ADD_PROJECT_DEPENDENCY(Eigen3 REQUIRED PKG_CONFIG_REQUIRES "eigen3 >= 3.0.5")
SET(PYTHON_COMPONENTS Interpreter Development NumPy)
FINDPYTHON(REQUIRED)
ADD_PROJECT_DEPENDENCY(eigenpy 2.7.14 REQUIRED)

SET(${PROJECT_NAME}_HEADERS
  include/${PROJECT_NAME}/fwd.hpp
  include/${PROJECT_NAME}/ad.hpp
  include/${PROJECT_NAME}/independent.hpp
  include/${PROJECT_NAME}/ad_fun.hpp
  include/${PROJECT_NAME}/cast.hpp
  include/${PROJECT_NAME}/cppad.hpp
  include/${PROJECT_NAME}/cppad-scalar.hpp
  include/${PROJECT_NAME}/utils/scope.hpp

  # Generated headers
  ${${PROJECT_NAME}_BINARY_DIR}/include/${PROJECT_NAME}/config.hpp
  ${${PROJECT_NAME}_BINARY_DIR}/include/${PROJECT_NAME}/deprecated.hpp
  ${${PROJECT_NAME}_BINARY_DIR}/include/${PROJECT_NAME}/warning.hpp
  )

SET(${PROJECT_NAME}_SOURCES
  src/cppad.cpp
  src/expose-type-double.cpp
  src/expose-type-double-row-major.cpp
  )

IF(BUILD_WITH_CPPAD_CODEGEN_BINDINGS)
  LIST(APPEND ${PROJECT_NAME}_HEADERS
    include/${PROJECT_NAME}/codegen/cg.hpp
    include/${PROJECT_NAME}/codegen/cppadcg-scalar.hpp
    include/${PROJECT_NAME}/codegen/code-handler.hpp
    include/${PROJECT_NAME}/codegen/lang/c/language-c.hpp
    include/${PROJECT_NAME}/codegen/lang/c/lang-c-default-var-name-gen.hpp
    )
ENDIF(BUILD_WITH_CPPAD_CODEGEN_BINDINGS)

ADD_LIBRARY(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_SOURCES} ${${PROJECT_NAME}_HEADERS})

IF(SUFFIX_SO_VERSION)
  SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION})
ENDIF(SUFFIX_SO_VERSION)

TARGET_LINK_BOOST_PYTHON(${PROJECT_NAME} PUBLIC)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} PUBLIC ${cppad_LIBRARY} eigenpy::eigenpy)
IF(BUILD_WITH_CPPAD_CODEGEN_BINDINGS)
  TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME}
    SYSTEM PUBLIC
    ${cppadcg_INCLUDE_DIR}
  )
  TARGET_LINK_LIBRARIES(${PROJECT_NAME} PUBLIC ${CMAKE_DL_LIBS})
ENDIF(BUILD_WITH_CPPAD_CODEGEN_BINDINGS)

IF(MSVC)
  TARGET_COMPILE_OPTIONS(${PROJECT_NAME} PUBLIC "/bigobj")
ENDIF()

# Do not report:
#  -Wconversion as the BOOST_PYTHON_FUNCTION_OVERLOADS implicitly converts.
#  -Wcomment as latex equations have multi-line comments.
IF(NOT WIN32)
  TARGET_COMPILE_OPTIONS(${PROJECT_NAME} PRIVATE -Wno-conversion -Wno-comment)
ENDIF(NOT WIN32)
IF(WIN32)
  TARGET_COMPILE_DEFINITIONS(${PROJECT_NAME} PRIVATE -DNOMINMAX)
  TARGET_LINK_LIBRARIES(${PROJECT_NAME} PUBLIC ${PYTHON_LIBRARY})
ENDIF(WIN32)

TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME}
  SYSTEM PUBLIC
  ${Boost_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
  ${PYTHON_INCLUDE_DIRS}
  $<INSTALL_INTERFACE:include>)
TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC $<INSTALL_INTERFACE:include>)

INSTALL(TARGETS ${PROJECT_NAME}
  EXPORT ${TARGETS_EXPORT_NAME}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_FULL_BINDIR})

ADD_HEADER_GROUP(${PROJECT_NAME}_HEADERS)
ADD_SOURCE_GROUP(${PROJECT_NAME}_SOURCES)

ADD_SUBDIRECTORY(python)
ADD_SUBDIRECTORY(example)

PKG_CONFIG_APPEND_LIBS(${PROJECT_NAME})
PKG_CONFIG_APPEND_CFLAGS("-I${PYTHON_INCLUDE_DIRS}")
PKG_CONFIG_APPEND_BOOST_LIBS(${BOOST_COMPONENTS})

setup_project_finalize()
