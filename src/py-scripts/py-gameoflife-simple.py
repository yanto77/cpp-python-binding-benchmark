from loader import module_name, PyGameOfLife
from loader import gameoflife_config as config
from helpers import CustomTimer

board = PyGameOfLife(config['rows'], config['cols'])
board.generate_board()
assert(board.count_alive_cells() == config['cells_start'])

t = CustomTimer(f'gameoflife, simple, {module_name}')
for i in range(config['iter']):
    next_board = board.clone()

    for row in range(config['rows']):
        for col in range(config['cols']):
            alive_self = board.get_cell(row, col)
            alive_around = board.count_alive_neighbors(row, col)

            if alive_self and (alive_around < 2 or alive_around > 3):
                next_board.set_cell(row, col, False)
            elif not alive_self and alive_around == 3:
                next_board.set_cell(row, col, True)

    board = next_board
t.stop()

assert(board.count_alive_cells() == config['cells_end'])
