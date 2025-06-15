add_library(
    hdg_clt_static
    STATIC
    src/hdg_clt.cpp
)
target_link_libraries(hdg_clt_static PUBLIC libhdg)

add_executable(
    hdg_clt
    main.cpp
)

target_link_libraries(
    hdg_clt 
    PUBLIC 
    "hdg_clt_static"
    "libhdg"
)