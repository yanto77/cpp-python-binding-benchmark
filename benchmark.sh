PYTHON_EXEC=/usr/bin/python3.10
PYPY_EXEC=/usr/bin/pypy3
CPYTHON_MODULES=(
    pkg_cython
    pkg_swig 
    pkg_manual 
    pkg_cffi 
    pkg_nanobind 
    pkg_pybind11 
    pkg_cppyy
)
PYPY_MODULES=(
    # pkg_cython # this produces extremely poor results, 
    pkg_cffi 
)

function run_mandelbrot_test 
{
    ./cpp-mandelbrot-single
    ./cpp-mandelbrot-simple
    ./cpp-mandelbrot-complex

    for mod in "${CPYTHON_MODULES[@]}"
    do
        $PYTHON_EXEC ./py_scripts/py-mandelbrot-single.py --module "$mod"
        $PYTHON_EXEC ./py_scripts/py-mandelbrot-simple.py --module "$mod"
        $PYTHON_EXEC ./py_scripts/py-mandelbrot-complex.py --module "$mod"
    done

    for mod in "${PYPY_MODULES[@]}"
    do
        $PYPY_EXEC ./py_scripts/py-mandelbrot-single.py --module "$mod"
        $PYPY_EXEC ./py_scripts/py-mandelbrot-simple.py --module "$mod"
        $PYPY_EXEC ./py_scripts/py-mandelbrot-complex.py --module "$mod"
    done
}

function run_gameoflife_test 
{
    ./cpp-gameoflife-single
    ./cpp-gameoflife-simple
    ./cpp-gameoflife-complex

    for mod in "${CPYTHON_MODULES[@]}"
    do
        $PYTHON_EXEC ./py_scripts/py-gameoflife-single.py --module "$mod"
        $PYTHON_EXEC ./py_scripts/py-gameoflife-simple.py --module "$mod"
        $PYTHON_EXEC ./py_scripts/py-gameoflife-complex.py --module "$mod"
    done

    for mod in "${PYPY_MODULES[@]}"
    do
        $PYPY_EXEC ./py_scripts/py-gameoflife-single.py --module "$mod"
        $PYPY_EXEC ./py_scripts/py-gameoflife-simple.py --module "$mod"
        $PYPY_EXEC ./py_scripts/py-gameoflife-complex.py --module "$mod"
    done
}

function main 
{
    cd ./build/bin
    export LD_LIBRARY_PATH=./lib

    run_mandelbrot_test
    run_gameoflife_test
}

main