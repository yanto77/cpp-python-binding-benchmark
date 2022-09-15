cmake_minimum_required(VERSION 3.16)
project(cpp-exec)

configure_file(config.h.in config.h)

function(addExec execName)
    set(targetName cpp-${execName})
    add_executable(${targetName} exec-${execName}.cpp)
    target_include_directories(${targetName} PRIVATE 
        ${CMAKE_SOURCE_DIR}/src/
        ${CMAKE_CURRENT_BINARY_DIR}
    )
    target_link_libraries(${targetName} PRIVATE cpp-mandelbrot-lib)
    set_target_properties(${targetName} PROPERTIES CXX_STANDARD 17)
endfunction()

addExec(mandelbrot-single)
addExec(mandelbrot-simple)
addExec(mandelbrot-complex)

addExec(gameoflife-single)
addExec(gameoflife-simple)
addExec(gameoflife-complex)