file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# # hdg 可执行文件
# add_executable(hdg main.cpp "${SOURCES}")
# target_include_directories(hdg PUBLIC "${SML_INCLUDE_DIR}")

# hdg 库文件，测试框架将会引用该共享库
add_library(libhdg SHARED "${SOURCES}")

if (CMAKE_CXX_COMPILE_ID STREQUAL "GNU")
    target_compile_options(
        libhdg 
        PRIVATE 
        -Wall -Wextra
        -Werror
        -Wno-unused-parameter
        -Wno-deprecated-copy
        -Wno-unused-variable
        -Werror=return-type   # 将返回值警告转为错误
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(
        libhdg 
        PRIVATE 
        /utf-8
    )
endif()

target_include_directories(
    libhdg 
    PUBLIC 
    "${SML_INCLUDE_DIR}"
    "${LIB_INCLUDE}"
)
