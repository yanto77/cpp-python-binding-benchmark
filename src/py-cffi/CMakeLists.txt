cmake_minimum_required(VERSION 3.16)
project(py-cffi)

add_custom_target(pkg_cffi ALL)
add_custom_command(TARGET pkg_cffi POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/pkg_cffi.py"
        "${CMAKE_BINARY_DIR}/bin/lib_python/pkg_cffi.py"
    COMMENT "Copying pkg_cffi.py folder in build dir"
)
