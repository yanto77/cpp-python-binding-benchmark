from loader import module_name, PyMandelbrot, PyVec2
from loader import mandelbrot_config as config
from helpers import write_ppm, CustomTimer

pixels = []

t = CustomTimer(f'mandelbrot, single, {module_name}')
pixels = PyMandelbrot.get_image(config['size'], config['iter'])
t.stop()

write_ppm(f'out-py-single({module_name}).ppm', config['size'], pixels)

