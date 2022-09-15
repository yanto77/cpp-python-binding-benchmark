cmake_minimum_required(VERSION 3.16)
project(py-cython)

# TODO: out-of-source build? copy all python files to ./build/src/py-cython using PRE_BUILD?

add_custom_target(pkg_cython_cpy ALL
    COMMAND /usr/bin/python3 setup.py build_ext --build-lib=${CMAKE_BINARY_DIR}/bin/${DIR_PY_MODULES}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    DEPENDS cpp-mandelbrot-lib
)

add_custom_target(pkg_cython_pypy ALL
    COMMAND /usr/bin/pypy3 setup.py build_ext --build-lib=${CMAKE_BINARY_DIR}/bin/${DIR_PY_MODULES}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    DEPENDS cpp-mandelbrot-lib
)