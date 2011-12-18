////////////////////////////////////////////////////////////////////////////////
///
/// @file   GameOfLifeTest.cpp
/// @brief  Test for GameOfLife
///

#include <gtest/gtest.h>
#include <sstream>

namespace
{
    const char* GENERATION_1[] =
    {
        "4 8",
        "........",
        "....*...",
        "...**...",
        "........"
    };

    const char* GENERATION_2[] =
    {
        "4 8",
        "........",
        "...**...",
        "...**...",
        "........"
    };
}

class GameOfLife
{
public:
    GameOfLife(int width, int height) :
        width_(width),
        height_(height)
    {
        std::vector<bool> row(width_, false);

        for (int i = 0; i < height_; i++)
            grid_.push_back(row);
    }

    GameOfLife(const char* start[])
    {
        std::istringstream stream(start[0]);
        stream >> height_ >> width_;

        std::vector<bool> row(width_, false);

        for (int i = 0; i < height_; i++)
        {
            for (int j = 0; j < width_; j++)
                row[j] = (start[i+1][j] == '*');

            grid_.push_back(row);
        }
    }

    bool operator==(const GameOfLife& rhs)
    {
        return width_ == rhs.width_ &&
               height_ == rhs.height_ &&
               grid_ == rhs.grid_;
    }

    int width() const
    {
        return width_;
    }

    int height() const
    {
        return height_;
    }

    std::vector<bool>& operator[](int index)
    {
        return grid_[index];
    }

    void nextGeneration()
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

    int liveNeighbors(int row, int col)
    {
        // xxx
        // xxx
        // xxx

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

    bool getState(int row, int col)
    {
        bool state = false;

        if (row >= 0 && row < height_ && col >= 0 && col < width_)
            state = grid_[row][col];

        return state;
    }

private:
    int width_;
    int height_;
    std::vector<std::vector<bool> > grid_;
};

class GameOfLifeTest : public ::testing::Test
{
public:
    GameOfLifeTest() : game(GENERATION_1) {}

    GameOfLife game;
};

TEST_F(GameOfLifeTest, GameWidthIsCorrect)
{
    EXPECT_EQ(8, game.width());
}

TEST_F(GameOfLifeTest, GameHeightIsCorrect)
{
    EXPECT_EQ(4, game.height());
}

TEST_F(GameOfLifeTest, DeadCellsAreCorrectlyInitialized)
{
    EXPECT_TRUE(false == game[0][0]);
}

TEST_F(GameOfLifeTest, LiveCellsAreCorrectlyInitialized)
{
    EXPECT_TRUE(true == game[1][4]);
}

TEST_F(GameOfLifeTest, NextStateIsCorrect)
{
    game.nextGeneration();

    GameOfLife game2(GENERATION_2);

    EXPECT_TRUE(game == game2);
}
