#include "cpp-lib/gameoflife.h"
#include "config.h"
#include "helpers.h"
#include <cassert>

int main()
{
    std::vector<color_t> pixels;

    {
        stack_timer_t t("gameoflife, simple, cpp");

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
            for (int row = 0; row < GAMEOFLIFE_ROWS; row++)
            {
                for (int col = 0; col < GAMEOFLIFE_COLS; col++)
                {
                    bool alive_self = board.get_cell(row, col);
                    size_t alive_around = board.count_alive_neighbors(row, col);

                    if (alive_self && (alive_around < 2 || alive_around > 3))
                    {
                        next_board.set_cell(row, col, false);
                    }
                    else if(!alive_self && alive_around == 3)
                    {
                        next_board.set_cell(row, col, true);
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
