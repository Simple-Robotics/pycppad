ADD_PYTHON_UNIT_TEST("${PROJECT_NAME}-add_eq" "example/add_eq.py" "python")
IF(BUILD_WITH_CPPAD_CODEGEN_BINDINGS)
  ADD_PYTHON_UNIT_TEST("${PROJECT_NAME}-cppadcg_c_codegen" "example/cppadcg_c_codegen.py" "python")
ENDIF()
