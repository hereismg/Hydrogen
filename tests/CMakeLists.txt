
add_executable(Test1 test1.cpp)
target_include_directories(Test1 PUBLIC ../include/basic ../include/kernel)
target_link_libraries(Test1 PUBLIC libhdg)
add_test(NAME test1 COMMAND Test1)

add_executable(Test2 test2.cpp)
target_include_directories(Test2 PUBLIC ../include/basic ../include/kernel)
target_link_libraries(Test2 PUBLIC libhdg)
add_test(NAME test2 COMMAND Test2)
