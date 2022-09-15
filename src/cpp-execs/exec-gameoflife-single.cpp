#include "cpp-lib/gameoflife.h"
#include "config.h"
#include "helpers.h"

int main()
{
    std::vector<color_t> pixels;

    {
        stack_timer_t t("gameoflife, single, cpp");

        auto board = GameOfLife(GAMEOFLIFE_ROWS, GAMEOFLIFE_COLS);
        board.generate_board();
        if (board.count_alive_cells() != GAMEOFLIFE_CELLS_START)
        {
            printf("ERR: Invalid number of cells at the start\n");
            exit(1);
        }

        for (int i = 0; i < GAMEOFLIFE_MAX_ITER; i++)
        {
            board.update_board();
        }

        if (board.count_alive_cells() != GAMEOFLIFE_CELLS_END)
        {
            printf("ERR: Invalid number of cells at the end\n");
            exit(1);
        }
    }

    return EXIT_SUCCESS;
}
