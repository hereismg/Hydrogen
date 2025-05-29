set(TEST_OUTPUT)
set(GOOGLE_TEST_DIR "${CMAKE_CURRENT_LIST_DIR}/tests/gtest-1.16")

set(
    TEST_INCLUDE_DIR 
    "${GTEST_INCLUDE_DIR}"
    "${SML_INCLUDE_DIR}"
    "${LIB_INCLUDE}"
    "${PROJECT_SOURCE_DIR}/hydrogen/include"
)

set(
    TEST_LINK_DIR
    "${GOOGLE_TEST_DIR}/build/lib"
    "${LIBRARY_OUTPUT_PATH}"
)

set(
    TEST_LINK_LIB
    "gtest"
    "gtest_main"
    libhdg
)


function(hdg_append_test test_name)
    add_executable("${test_name}" ${ARGN})

    target_link_directories    ("${test_name}" PUBLIC "${TEST_LINK_DIR}")
    target_link_libraries      ("${test_name}" PUBLIC "${TEST_LINK_LIB}")
    target_include_directories ("${test_name}" PUBLIC "${TEST_INCLUDE_DIR}")

    add_test(
        NAME "${test_name}" 
        COMMAND "${test_name}"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    )
endfunction()

hdg_append_test(
    "test_obj"
    "hdg/test_obj.cpp"
)

hdg_append_test(
    "test_ast"
    "hdg/test_ast.cpp"
)

hdg_append_test(
    "test_lexer"
    "hdg/test_lexer.cpp"
)

hdg_append_test(
    "test_parser" 
    "hdg/test_parser.cpp"
)
