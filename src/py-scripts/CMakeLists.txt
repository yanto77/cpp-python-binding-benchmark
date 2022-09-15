cmake_minimum_required (VERSION 3.16)
project (py-scripts)

# Copy static data relative to the executable
add_custom_target(py_scripts ALL)
add_custom_command(TARGET py_scripts POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "${PROJECT_SOURCE_DIR}/*.py"
        "${CMAKE_BINARY_DIR}/bin/py_scripts"
    COMMENT "Copying py-script folder in build dir"
)

configure_file(loader.py.in "${CMAKE_BINARY_DIR}/bin/py_scripts/loader.py")