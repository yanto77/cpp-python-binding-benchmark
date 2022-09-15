#pragma once
#include "stddef.h"
#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    void* data;
} c_gameoflife_t;

c_gameoflife_t* cgameoflife_alloc(int rows, int cols);
void cgameoflife_dealloc(c_gameoflife_t* board);

c_gameoflife_t* cgameoflife_clone(c_gameoflife_t* board);
void cgameoflife_generate_board(c_gameoflife_t* board);
uint8_t cgameoflife_count_alive_neighbors(c_gameoflife_t* board, int row, int col);
size_t cgameoflife_count_alive_cells(c_gameoflife_t* board);
void cgameoflife_update_board(c_gameoflife_t* board);
bool cgameoflife_get_cell(c_gameoflife_t* board, int row, int col);
void cgameoflife_set_cell(c_gameoflife_t* board, int row, int col, bool value);

#ifdef __cplusplus
}
#endif