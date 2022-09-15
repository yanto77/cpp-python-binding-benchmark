from loader import module_name, PyMandelbrot, PyVec2
from loader import mandelbrot_config as config
from helpers import write_ppm, CustomTimer

pixels = []

t = CustomTimer(f'mandelbrot, complex, {module_name}')
for i in range(config['size'].x):
    for j in range(config['size'].y):
        point = PyVec2(i, j)
        sp = PyMandelbrot.scale(point, config['size'])
        it_count = PyMandelbrot.get_iterations(sp, config['iter'])
        color = PyMandelbrot.get_rgb_smooth(it_count, config['iter'])
        pixels.append(color)
t.stop()

write_ppm(f'out-py-complex-loop({module_name}).ppm', config['size'], pixels)