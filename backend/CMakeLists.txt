file(GLOB_RECURSE source *.cpp)

add_executable(backend ${source})

target_link_libraries(backend)
