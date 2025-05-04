add_executable(
    hdg_clt
    ./src/main.cpp
)
target_link_directories(hdg_clt PUBLIC ../bin)
target_link_libraries(hdg_clt PUBLIC libhdg)