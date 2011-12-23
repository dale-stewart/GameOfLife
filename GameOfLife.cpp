////////////////////////////////////////////////////////////////////////////////
///
/// @file   GameOfLife.cpp
/// @brief  Implements Conway's Game of Life
///

#include "GameOfLife.h"
#include <sstream>

GameOfLife::GameOfLife(int width, int height) :
    width_(width),
    height_(height),
    generation_(1)
{
    std::vector<bool> row(width_, false);

    for (int i = 0; i < height_; i++)
        grid_.push_back(row);
}

GameOfLife::GameOfLife(const char* start[])
{
    std::istringstream stream(start[0]);
    std::string gen;
    stream >> gen >> generation_;

    std::istringstream stream2(start[1]);
    stream2 >> height_ >> width_;

    std::vector<bool> row(width_, false);

    for (int i = 0; i < height_; i++)
    {
        for (int j = 0; j < width_; j++)
            row[j] = (start[i+2][j] == '*');

        grid_.push_back(row);
    }
}

bool GameOfLife::operator==(const GameOfLife& rhs)
{
    return width_ == rhs.width_ &&
           height_ == rhs.height_ &&
           grid_ == rhs.grid_;
}

int GameOfLife::width() const
{
    return width_;
}

int GameOfLife::height() const
{
    return height_;
}

std::vector<bool>& GameOfLife::operator[](int index)
{
    return grid_[index];
}

void GameOfLife::nextGeneration()
{
    // 1. Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
    // 2. Any live cell with more than three live neighbours dies, as if by overcrowding.
    // 3. Any live cell with two or three live neighbours lives on to the next generation.
    // 4. Any dead cell with exactly three live neighbours becomes a live cell.

    GameOfLife game2(width_, height_);

    for (int i = 0; i < height_; i++)
    {
        for (int j = 0; j < width_; j++)
        {
            int live = liveNeighbors(i, j);

            if (grid_[i][j])
            {
                if (live < 2 || live > 3)
                    game2[i][j] = false;
                else
                    game2[i][j] = true;
            }
            else
            {
                if (live == 3)
                    game2[i][j] = true;
                else
                    game2[i][j] = false;
            }
        }
    }

    grid_ = game2.grid_;
}

int GameOfLife::liveNeighbors(int row, int col)
{
    int count = 0;

    int up = row - 1;
    int left = col - 1;
    int down = row + 1;
    int right = col + 1;

    if (getState(up, left))
        ++count;

    if (getState(up, col))
        ++count;

    if (getState(up, right))
        ++count;

    if (getState(row, left))
        ++count;

    if (getState(row, right))
        ++count;

    if (getState(down, left))
        ++count;

    if (getState(down, col))
        ++count;

    if (getState(down, right))
        ++count;

    return count;
}

bool GameOfLife::getState(int row, int col)
{
    bool state = false;

    if (row >= 0 && row < height_ && col >= 0 && col < width_)
        state = grid_[row][col];

    return state;
}

std::ostream& operator<<(std::ostream& stream, GameOfLife& game)
{
    stream << "Generation " << game.generation_ << ":" << std::endl;
    stream << game.height_ << " " << game.width_ << std::endl;

    for (int i = 0; i < game.height_; i++)
    {
        for (int j = 0; j < game.width_; j++)
            stream << (game.grid_[i][j] ? "*" : ".");

        stream << std::endl;
    }

    return stream;
}

