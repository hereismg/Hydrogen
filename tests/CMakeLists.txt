#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/tests/build)

set(TEST_OUTPUT)
set(GOOGLE_TEST_DIR "${CMAKE_CURRENT_LIST_DIR}/tests/gtest-1.16")

# file(GLOB_RECURSE TEST_CASE ${PROJECT_SOURCE_DIR}/tests/src/*.cpp)
# foreach(test_src ${TEST_CASE})
#     get_filename_component(test_name ${test_src} NAME_WE)
#     add_executable(${test_name} ${test_src})
#     target_include_directories(
#             ${test_name}
#             PUBLIC
#             "${GTEST_INCLUDE_DIR}"
#             "${SML_INCLUDE_DIR}"
#             "${PROJECT_SOURCE_DIR}/hydrogen/include/basic"
#             "${PROJECT_SOURCE_DIR}/hydrogen/include/kernel"
#             "${PROJECT_SOURCE_DIR}/hydrogen/include/node"
# #            "${PROJECT_SOURCE_DIR}/include/object"
#     )
#     target_link_directories(
#             ${test_name}
#             PUBLIC
#             "${GOOGLE_TEST_DIR}/build/lib"
#             "${LIBRARY_OUTPUT_PATH}"
#     )
#     target_link_libraries(
#             ${test_name}
#             PUBLIC
#             "gtest" "gtest_main"
#     )
#     target_link_libraries(${test_name} PRIVATE libhdg)
#     add_test(NAME ${test_name} COMMAND ${test_name})
# endforeach()

function(hdg_append_test_with_file file)
    get_filename_component(name ${file} NAME_WE)
    add_executable(${name} ${file})

    target_include_directories(
        ${name}
        PUBLIC
        "${GTEST_INCLUDE_DIR}"
        "${SML_INCLUDE_DIR}"
        "${PROJECT_SOURCE_DIR}/hydrogen/include/basic"
        "${PROJECT_SOURCE_DIR}/hydrogen/include/kernel"
        "${PROJECT_SOURCE_DIR}/hydrogen/include/node"
#            "${PROJECT_SOURCE_DIR}/include/object"
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
            "gtest" "gtest_main"
    )
    target_link_libraries(${name} PRIVATE libhdg)
    add_test(NAME ${name} COMMAND ${name})
endfunction()

function(hdg_append_test_with_dir dir)
    get_filename_component(test_name ${dir} NAME)
    set(test_name "test_${test_name}")

    add_executable(${test_name} "${dir}/${test_name}.cpp")

    target_include_directories(
        ${test_name}
        PUBLIC
        "${GTEST_INCLUDE_DIR}"
        "${SML_INCLUDE_DIR}"
        "${PROJECT_SOURCE_DIR}/hydrogen/include/basic"
        "${PROJECT_SOURCE_DIR}/hydrogen/include/kernel"
        "${PROJECT_SOURCE_DIR}/hydrogen/include/node"
#            "${PROJECT_SOURCE_DIR}/include/object"
    )
    target_link_directories(
            ${test_name}
            PUBLIC
            "${GOOGLE_TEST_DIR}/build/lib"
            "${LIBRARY_OUTPUT_PATH}"
    )
    target_link_libraries(
            ${test_name}
            PUBLIC
            "gtest" "gtest_main"
    )
    target_link_libraries(${test_name} PRIVATE libhdg)
    add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()

hdg_append_test_with_file("src/test_newLexer.cpp")
hdg_append_test_with_dir("src/parse")