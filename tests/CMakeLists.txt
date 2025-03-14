#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/tests/build)
# add_subdirectory(gtest-1.16)

set(TEST_OUTPUT)
set(GOOGLE_TEST_DIR "${CMAKE_CURRENT_LIST_DIR}/tests/gtest-1.16")

file(GLOB_RECURSE TEST_CASE ${PROJECT_SOURCE_DIR}/tests/src/*.cpp)
foreach(test_src ${TEST_CASE})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name} ${test_src})
    target_include_directories(
            ${test_name}
            PUBLIC
            "${GOOGLE_TEST_DIR}/googletest/include"
            "${GOOGLE_TEST_DIR}/googlemock/include"
            "${SML_INCLUDE_DIR}"
            "${PROJECT_SOURCE_DIR}/include/basic"
            "${PROJECT_SOURCE_DIR}/include/kernel"
            "${PROJECT_SOURCE_DIR}/include/node"
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
endforeach()
