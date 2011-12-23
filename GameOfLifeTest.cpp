////////////////////////////////////////////////////////////////////////////////
///
/// @file   GameOfLifeTest.cpp
/// @brief  Test for GameOfLife
///

#include <gtest/gtest.h>
#include "GameOfLife.h"
#include <sstream>

namespace
{
    const char* GENERATION_1[] =
    {
        "Generation 1:",
        "4 8",
        "........",
        "....*...",
        "...**...",
        "........"
    };

    const char* GENERATION_2[] =
    {
        "Generation 2:",
        "4 8",
        "........",
        "...**...",
        "...**...",
        "........"
    };
}

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

TEST_F(GameOfLifeTest, ProducesCorrectTextOutput)
{
    std::ostringstream actualStream;
    std::ostringstream expectedStream;

    actualStream << game;

    for (size_t i = 0; i < sizeof(GENERATION_1)/sizeof(GENERATION_1[0]); i++)
        expectedStream << GENERATION_1[i] << std::endl;

    EXPECT_EQ(expectedStream.str(), actualStream.str());
}
