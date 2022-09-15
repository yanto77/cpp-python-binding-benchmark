from loader import module_name, PyGameOfLife
from loader import gameoflife_config as config
from helpers import CustomTimer

board = PyGameOfLife(config['rows'], config['cols'])
board.generate_board()
assert(board.count_alive_cells() == config['cells_start'])

t = CustomTimer(f'gameoflife, single, {module_name}')
for i in range(config['iter']):
    board.update_board()
t.stop()

assert(board.count_alive_cells() == config['cells_end'])
