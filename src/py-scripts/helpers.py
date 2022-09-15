import time

def write_ppm(fname, size, pixels):
    with open(fname, 'w') as file:
        file.write(f'P3\n')
        file.write(f'{size.x} {size.y} 255\n')
        for color in pixels:
            file.write(f'{color.r} {color.g} {color.b}\n')

class CustomTimer:
    def __init__(self, msg):
        self._t0 = time.perf_counter()
        self._msg = msg

    def stop(self):
        elapsed = time.perf_counter() - self._t0
        print(f"{self._msg}, {elapsed:0.3f} sec")
