cmake_minimum_required(VERSION 3.16)
project(py-cppyy)

add_custom_target(pkg_cppyy ALL)
add_custom_command(TARGET pkg_cppyy POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/pkg_cppyy.py"
        "${CMAKE_BINARY_DIR}/bin/lib_python/pkg_cppyy.py"
    COMMENT "Copying pkg_cppyy.py folder in build dir"
)
