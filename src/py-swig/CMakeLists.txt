cmake_minimum_required(VERSION 3.16)
project(py-swig)

# TODO: out-of-source build? copy all python files to ./build/src/py-swig using PRE_BUILD?

add_custom_target(pkg_swig ALL
    COMMAND /usr/bin/python3 setup.py build_ext --build-lib=${CMAKE_BINARY_DIR}/bin/${DIR_PY_MODULES}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    DEPENDS cpp-mandelbrot-lib
)

add_custom_command(TARGET pkg_swig POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/pkg_swig.py"
        "${CMAKE_BINARY_DIR}/bin/lib_python/pkg_swig.py"
    COMMENT "Copying pkg_swig.py folder in build dir"
)