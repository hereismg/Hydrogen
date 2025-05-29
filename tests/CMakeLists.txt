set(TEST_OUTPUT)
set(GOOGLE_TEST_DIR "${CMAKE_CURRENT_LIST_DIR}/tests/gtest-1.16")

set(
    TEST_INCLUDE_DIR 
    "${GTEST_INCLUDE_DIR}"
    "${SML_INCLUDE_DIR}"
    "${LIB_INCLUDE}"
    "${PROJECT_SOURCE_DIR}/hydrogen/include/basic"
    "${PROJECT_SOURCE_DIR}/hydrogen/include/kernel"
    "${PROJECT_SOURCE_DIR}/hydrogen/include/node"
    "${PROJECT_SOURCE_DIR}/hydrogen/include/object"
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

function(hdg_append_test_with_file file)
    if(NOT DEFINED TEST_LINK_DIR OR NOT DEFINED TEST_LINK_LIB OR NOT DEFINED TEST_INCLUDE_DIR)
        message(FATAL_ERROR "TEST_LINK_DIR/TEST_LINK_LIB/TEST_INCLUDE_DIR 未定义，无法构建测试")
    endif()

    get_filename_component(name ${file} NAME_WE)
    add_executable(${name} ${file})

    target_include_directories(
        ${name}
        PUBLIC
        "${GTEST_INCLUDE_DIR}"
        "${SML_INCLUDE_DIR}"
        "${PROJECT_SOURCE_DIR}/hydrogen/include"
        # "${PROJECT_SOURCE_DIR}/hydrogen/include/kernel"
        # "${PROJECT_SOURCE_DIR}/hydrogen/include/node"
        # "${PROJECT_SOURCE_DIR}/hydrogen/include/object"
        "${PROJECT_SOURCE_DIR}/clt/src"
    )
    target_link_directories(
            ${name}
            PUBLIC
            "${GOOGLE_TEST_DIR}/build/lib"
            "${LIBRARY_OUTPUT_PATH}"
    )
    target_link_libraries(
            ${name}
            PUBLIC
            "gtest"
            "gtest_main"
    )
    target_link_libraries(
        ${name} 
        PUBLIC 
        libhdg
        hdg_clt_static
    )
    add_test(NAME ${name} COMMAND ${name})
endfunction()


function(hdg_append_test_with_dir dir)
    get_filename_component(test_name ${dir} NAME)
    set(test_name "test_${test_name}")

    add_executable(${test_name} "${dir}/${test_name}.cpp")

    target_include_directories(
        ${test_name}
        PUBLIC
        "${TEST_INCLUDE_DIR}"
    )
    target_link_directories(
            ${test_name}
            PUBLIC
            "${GOOGLE_TEST_DIR}/build/lib"
            "${LIBRARY_OUTPUT_PATH}"
    )
    target_link_libraries(${test_name} PUBLIC "${TEST_LINK_LIB}")
    add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()

hdg_append_test_with_file("src/test_newLexer.cpp")
hdg_append_test_with_dir("src/lexer")

hdg_append_test_with_file("clt/test_option.cpp")
hdg_append_test_with_file("src/test_ast.cpp")
hdg_append_test_with_file("src/test_obj.cpp")

hdg_append_test("test_parser" 
    "src/parser/test_parser.cpp"
)
