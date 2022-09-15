from setuptools import setup, Extension

extensions = [
    Extension(
        name="_pkg_swig", # SWIG requires _ as a prefix for the module name
        sources=["pkg_swig.i"], 
        include_dirs=['../cpp-lib/'],
        libraries=["cpp-mandelbrot-lib"],
        library_dirs=["../../build/bin/lib/"],
        extra_compile_args=["-std=c++0x", "-O3", "-Wno-unused-variable"], 
        # Basic
        # swig_opts=['-py3', '-c++'],
        # Ref: 32.4.2 https://www.swig.org/Doc4.0/Python.html
        swig_opts=['-py3', '-c++', '-builtin'],
        # Ref: 32.6.5 https://www.swig.org/Doc4.0/Python.html
        # swig_opts=['-py3', '-c++', '-fastproxy', '-olddefs'],
    )
]

setup(name="pkg_swig", ext_modules=extensions)