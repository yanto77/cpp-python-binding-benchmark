#include "gameoflife.h"
#include <random>

GameOfLife::GameOfLife(int rows, int cols)
    : m_cols(cols)
    , m_rows(rows)
    , m_board(rows * cols, false)
{
}

GameOfLife::GameOfLife(const GameOfLife& other)
    : m_cols(other.m_cols)
    , m_rows(other.m_rows)
    , m_board(other.m_board)
{
}

GameOfLife* GameOfLife::clone()
{
    return new GameOfLife(*this);
}

void GameOfLife::generate_board()
{
    std::mt19937 gen(123456);
    std::uniform_int_distribution<> distrib(1, 3);

    for (int row = 0; row < m_rows; row++)
        for (int col = 0; col < m_cols; col++)
            if (distrib(gen) == 1) // 33% chance
                set_cell(row, col, true);
}

uint8_t GameOfLife::count_alive_neighbors(int cell_row, int cell_col)
{
    uint8_t alive = 0;

    for (int delta_row = -1; delta_row <= 1; delta_row++)
    {
        for (int delta_col = -1; delta_col <= 1; delta_col++)
        {
            const int row = cell_row + delta_row;
            const int col = cell_col + delta_col;

            if (delta_row == 0 || delta_col == 0)
                continue;

            if (row < 0 || row >= m_rows)
                continue;
            if (col < 0 || col >= m_cols)
                continue;

            if (get_cell(row, col))
                alive++;
        }
    }

    return alive;
}

size_t GameOfLife::count_alive_cells()
{
    size_t alive = 0;
    for (int row = 0; row < m_rows; row++)
        for (int col = 0; col < m_cols; col++)
            if (get_cell(row, col))
                alive++;

    return alive;
}

void GameOfLife::update_board()
{
    auto copy = *this;
    for (int row = 0; row < m_rows; row++)
    {
        for (int col = 0; col < m_cols; col++)
        {
            bool alive = get_cell(row, col);
            uint8_t neighbors = count_alive_neighbors(row, col);

            if (alive && (neighbors < 2 || neighbors > 3))
            {
                copy.set_cell(row, col, false);
            }
            else if (!alive && (neighbors == 3))
            {
                copy.set_cell(row, col, true);
            }
        }
    }
    m_board = copy.m_board;
}

bool GameOfLife::get_cell(int row, int col)
{
    return m_board[row * m_rows + col];
}

void GameOfLife::set_cell(int row, int col, bool value)
{
    m_board[row * m_rows + col] = value;
}
