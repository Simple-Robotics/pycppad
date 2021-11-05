PyCppAD — Python bindings for CppAD Automatic Differentiation library
======

<p align="center">
    <a href="https://opensource.org/licenses/BSD-3-Clause"><img src="https://img.shields.io/badge/License-BSD%203--Clause-green.svg" alt="License"/></a>
    <a href="https://gitlab.laas.fr/Simple-Robotics/pycppad/commits/master"><img src="https://gitlab.laas.fr/Simple-Robotics/pycppad/badges/master/pipeline.svg" alt="Pipeline status" /></a>
    <a href="http://projects.laas.fr/gepetto/doc/Simple-Robotics/pycppad/master/coverage/"><img src="https://gitlab.laas.fr/Simple-Robotics/pycppad/badges/master/coverage.svg?job=doc-coverage" alt="Coverage report" /></a>
    <a href="https://anaconda.org/conda-forge/pycppad"><img src="https://img.shields.io/conda/dn/conda-forge/pycppad.svg" alt="Conda Downloads"/></a>
    <a href="https://anaconda.org/conda-forge/pycppad"><img src="https://img.shields.io/conda/vn/conda-forge/pycppad.svg" alt="Conda Version"/></a>
    <a href="https://badge.fury.io/py/pycppad"><img src="https://badge.fury.io/py/pycppad.svg" alt="PyPI version"></a>
</p>

**PyCppAD** is an open source framework which provides bindings for the CppAD Automatic Differentiation([CppAD](https://coin-or.github.io/CppAD/doc/cppad.htm)) C++ library in Python.
**PyCppAD** also includes support for the CppADCodeGen ([CppADCodeGen](https://github.com/joaoleal/CppADCodeGen)), C++ library, which exploits CppAD functionality to perform code generation.

## Installing PyCppAD

### Installation via <img src="https://s3.amazonaws.com/conda-dev/conda_logo.svg" height="18">

As simple as that:
```bash
   conda install pycppad -c conda-forge
```

### Installation via PyPI

As simple as that:
```bash
   pip install pycppad
```

### Installation by source

#### Dependencies

PyCppAD dependes on the following dependencies:
* [Boost.Python](http://boostorg.github.io/python/doc/html/index.html)
* [Eigen3](https://eigen.tuxfamily.org)
* [EigenPy](https://github.com/stack-of-tasks/eigenpy)
* [CppAD](https://coin-or.github.io/CppAD/doc/install.htm)
* [CppADCodeGen](https://github.com/joaoleal/CppADCodeGen) (Optional)

#### Compiling PyCppAD

Once the dependencies have been installed, follow the following commands to compile PyCppAD:

```
cd ${path_to_your_development_source}/
git clone --recursive https://github.com/Simple-Robotics/pycppad.git
cd pycppad
mkdir _build-RELEASE
cd _build-RELEASE
cmake .. -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_INSTALL_PREFIX=${path_to_your_installation}
make install
```

Set up the `path_to_your_installation` and `path_to_your_development_source` based on your personal development environment.

Alternatively, in order to compile with [CppADCodeGen](https://github.com/joaoleal/CppADCodeGen) support, add `-DBUILD_WITH_CPPAD_CODEGEN_BINDINGS=ON` to the cmake command, and follow the build sequence as before:

```
cmake .. -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_INSTALL_PREFIX=${path_to_your_installation} -DBUILD_WITH_CPPAD_CODEGEN_BINDINGS=ON
```

## Acknowledgments

The development of **PyCppAD** is supported by the [Willow team](https://www.di.ens.fr/willow/) [@INRIA](http://www.inria.fr).
