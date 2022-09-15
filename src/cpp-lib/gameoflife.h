#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>

class GameOfLife
{
public:
    GameOfLife(int rows, int cols);
    GameOfLife(const GameOfLife& other);

    GameOfLife* clone();
    void generate_board();
    uint8_t count_alive_neighbors(int row, int col);
    size_t count_alive_cells();
    void update_board();
    bool get_cell(int row, int col);
    void set_cell(int row, int col, bool value);

private:
    int m_cols;
    int m_rows;
    std::vector<bool> m_board;
};

