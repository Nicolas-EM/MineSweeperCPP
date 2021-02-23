// game.h
#ifndef _GAME_H
#define _GAME_H
#include <iostream>
#include <time.h>
#include <limits>
#include <vector>

struct game{
    int numOfRows, numOfCols, numOfBombs;
    std::vector<std::vector<char>> userBoard;
    std::vector<std::vector<int>> gameBoard;

    // Constructor
    game(const int difficulty);

    // Returns true if point (X,Y) is within bounds
    bool withinBounds(const int xPos, const int yPos);
    
    // Returns number of bombs around point (X,Y)
    int numOfNearbyBombs(const int xPos, const int yPos);

    // Generate board with random bomb positions
    void generateBoard();

    // Print gameboard (for debugging purposes)
    void printGameBoard();

    // Print player's board
    void printUserBoard();

    // Void choose row and column
    void choosePoint(int &row, int &col);

    // Recursive function to update user board
    void updateUserBoard(const int xPos, const int yPos);

    // Print board solution
    void endGamePrint();

    // Check winCondition and terminate game
    bool winConditon();

};

#endif