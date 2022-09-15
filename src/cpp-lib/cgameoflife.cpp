#include "cgameoflife.h"
#include "gameoflife.h"

c_gameoflife_t* cgameoflife_alloc(int rows, int cols)
{
    auto* wrapper = new c_gameoflife_t();
    wrapper->data = new GameOfLife(rows, cols);
    return wrapper;
}

void cgameoflife_dealloc(c_gameoflife_t* board)
{
    auto* ptr = (GameOfLife*)board->data;
    delete (GameOfLife*)ptr;
    ptr = nullptr;
}

c_gameoflife_t* cgameoflife_clone(c_gameoflife_t* board)
{
    auto* ptr = (GameOfLife*)board->data;
    auto* wrapper = new c_gameoflife_t();
    wrapper->data = new GameOfLife(*ptr);
    return wrapper;
}

void cgameoflife_generate_board(c_gameoflife_t* board)
{
    auto* ptr = (GameOfLife*)board->data;
    ptr->generate_board();
}

uint8_t cgameoflife_count_alive_neighbors(c_gameoflife_t* board, int row, int col)
{
    auto* ptr = (GameOfLife*)board->data;
    return ptr->count_alive_neighbors(row, col);
}

size_t cgameoflife_count_alive_cells(c_gameoflife_t* board)
{
    auto* ptr = (GameOfLife*)board->data;
    return ptr->count_alive_cells();
}

void cgameoflife_update_board(c_gameoflife_t* board)
{
    auto* ptr = (GameOfLife*)board->data;
    ptr->update_board();
}

bool cgameoflife_get_cell(c_gameoflife_t* board, int row, int col)
{
    auto* ptr = (GameOfLife*)board->data;
    return ptr->get_cell(row, col);
}

void cgameoflife_set_cell(c_gameoflife_t* board, int row, int col, bool value)
{
    auto* ptr = (GameOfLife*)board->data;
    ptr->set_cell(row, col, value);
}
