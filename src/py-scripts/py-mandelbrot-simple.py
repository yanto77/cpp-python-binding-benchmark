from loader import module_name, PyMandelbrot, PyVec2
from loader import mandelbrot_config as config
from helpers import write_ppm, CustomTimer

pixels = []

t = CustomTimer(f'mandelbrot, simple, {module_name}')
for i in range(config['size'].x):
    for j in range(config['size'].y):
        point = PyVec2(i, j)
        color = PyMandelbrot.get_color(point, config['size'], config['iter'])
        pixels.append(color)
t.stop()

write_ppm(f'out-py-simple({module_name}).ppm', config['size'], pixels)
