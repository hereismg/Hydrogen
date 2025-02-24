set(CTEST_BINARY_DIRECTORY ${PROJECT_SOURCE_DIR}/tests/build)

file(GLOB TEST_CASE ${PROJECT_SOURCE_DIR}/tests/*.cpp)
foreach (test_src ${TEST_CASE})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name} ${test_src})
    target_include_directories(
            ${test_name}
            PUBLIC
            "./gtest/googletest/include"
            "./gtest/googlemock/include"
            "${PROJECT_SOURCE_DIR}/include/basic"
#            "${PROJECT_SOURCE_DIR}/include/error"
#            "${PROJECT_SOURCE_DIR}/include/kernel"
#            "${PROJECT_SOURCE_DIR}/include/node"
#            "${PROJECT_SOURCE_DIR}/include/object"
    )
    target_link_directories(
            ${test_name}
            PUBLIC
            "./gtest/build/lib"
            "${PROJECT_SOURCE_DIR}/bin"
    )
    target_link_libraries(
            ${test_name}
            PUBLIC
            "gtest" "gtest_main" "gmock" "gmock_main"
    )
#    target_link_libraries(${test_name} PRIVATE libhdg)
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach ()
