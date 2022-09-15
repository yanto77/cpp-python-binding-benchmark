#include "cpp-lib/gameoflife.h"
#include "config.h"
#include "helpers.h"
#include <cassert>

int main()
{
    std::vector<color_t> pixels;

    {
        stack_timer_t t("gameoflife, complex, cpp");

        auto board = GameOfLife(GAMEOFLIFE_ROWS, GAMEOFLIFE_COLS);
        board.generate_board();
        if (board.count_alive_cells() != GAMEOFLIFE_CELLS_START)
        {
            printf("ERR: Invalid number of cells at the start\n");
            exit(1);
        }

        for (int i = 0; i < GAMEOFLIFE_MAX_ITER; i++)
        {
            auto next_board = board;
            for (int cell_row = 0; cell_row < GAMEOFLIFE_ROWS; cell_row++)
            {
                for (int cell_col = 0; cell_col < GAMEOFLIFE_COLS; cell_col++)
                {
                    bool alive_self = board.get_cell(cell_row, cell_col);
                    size_t alive_around = 0;

                    for (int delta_row = -1; delta_row <= 1; delta_row++)
                    {
                        for (int delta_col = -1; delta_col <= 1; delta_col++)
                        {
                            const int row = cell_row + delta_row;
                            const int col = cell_col + delta_col;

                            if (delta_row == 0 || delta_col == 0)
                                continue;

                            if (row < 0 || row >= GAMEOFLIFE_ROWS)
                                continue;
                            if (col < 0 || col >= GAMEOFLIFE_COLS)
                                continue;

                            if (board.get_cell(row, col))
                                alive_around++;
                        }
                    }

                    if (alive_self && (alive_around < 2 || alive_around > 3))
                    {
                        next_board.set_cell(cell_row, cell_col, false);
                    }
                    else if(!alive_self && alive_around == 3)
                    {
                        next_board.set_cell(cell_row, cell_col, true);
                    }
                }
            }
            board = next_board;
        }

        if (board.count_alive_cells() != GAMEOFLIFE_CELLS_END)
        {
            printf("ERR: Invalid number of cells at the end\n");
            exit(1);
        }
    }

    return EXIT_SUCCESS;
}
