from loader import module_name, PyGameOfLife
from loader import gameoflife_config as config
from helpers import CustomTimer

board = PyGameOfLife(config['rows'], config['cols'])
board.generate_board()
assert(board.count_alive_cells() == config['cells_start'])

t = CustomTimer(f'gameoflife, complex, {module_name}')
for i in range(config['iter']):
    next_board = board.clone()

    for cell_row in range(config['rows']):
        for cell_col in range(config['cols']):
            alive_self = board.get_cell(cell_row, cell_col)

            alive_around = 0
            for delta_row in range(-1, 2):
                for delta_col in range(-1, 2):
                    row = cell_row + delta_row
                    col = cell_col + delta_col

                    if (delta_row == 0 or delta_col == 0):
                        continue

                    if (row < 0 or row >= config['rows']):
                        continue
                        
                    if (col < 0 or col >= config['cols']):
                        continue

                    if (board.get_cell(row, col)):
                        alive_around += 1


            if alive_self and (alive_around < 2 or alive_around > 3):
                next_board.set_cell(cell_row, cell_col, False)
            elif not alive_self and alive_around == 3:
                next_board.set_cell(cell_row, cell_col, True)

    board = next_board
t.stop()

assert(board.count_alive_cells() == config['cells_end'])
