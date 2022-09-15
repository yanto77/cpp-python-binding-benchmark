from setuptools import setup, Extension
from Cython.Build import cythonize
import os 

# NB: Using glob patterns [1] generates _distinct_ modules for each input file, 
# which is not what is wanted here. To combine all wrappers in a _single_ module,
# it's possible to either mash all *.pyx files into one (the approach taken here),
# or extend module finder [2].
#
# Refs:
# - [1] https://cython.readthedocs.io/en/latest/src/userguide/source_files_and_compilation.html#multiple-cython-files-in-a-package
# - [2] https://stackoverflow.com/q/30157363

if not os.path.exists('./build'):
    os.makedirs('./build')

includesContents = ""
for f in os.listdir("./"):
    if f.endswith(".pyx"):
        includesContents += "include \"" + f + "\"\n"

includesFile = open("./build/pkg_cython.pyx", "w")
includesFile.write(includesContents)
includesFile.close()

extensions = [
    Extension("pkg_cython",
        sources=["build/pkg_cython.pyx"], 
        include_dirs=['../cpp-lib/'],
        libraries=["cpp-mandelbrot-lib"],
        library_dirs=["../../build/bin/lib/"],
        extra_compile_args=["-O3"], 
        language="c++"
    )
]

setup(
    ext_modules=cythonize(
        extensions,
        compiler_directives={'language_level' : "3"}
    )
)