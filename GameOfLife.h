////////////////////////////////////////////////////////////////////////////////
///
/// @file   GameOfLife.h
/// @brief  Implements Conway's Game of Life
///

#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include <vector>

class GameOfLife
{
public:
    GameOfLife(int width, int height);
    GameOfLife(const char* start[]);

    bool operator==(const GameOfLife& rhs);

    int width() const;
    int height() const;

    std::vector<bool>& operator[](int index);

    void nextGeneration();

private:
    int liveNeighbors(int row, int col);
    bool getState(int row, int col);

    int width_;
    int height_;
    std::vector<std::vector<bool> > grid_;
};


#endif // GAMEOFLIFE_H
