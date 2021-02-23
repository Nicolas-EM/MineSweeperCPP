/*
Author: Nicolas ESPINOSA MOOSER
Created: 28th Nov 2020
*/

#include "game.cpp"
using namespace std;

bool endGame = false;
bool exitProgram = false;

int difficultySelection();

int main(){
    for(int i = 0; i < 52; i++) cout << "=";
    cout << "\nWelcome to Nico's Fantastic Minesweeper!\n";
    for(int i = 0; i < 52; i++) cout << "=";
    cout << "\n";
    do{
        int difficulty;
        difficulty = difficultySelection();
        game Game(difficulty);
        Game.generateBoard();
        // Game.printGameBoard();   // For debugging purposes
        
        do{
            Game.printUserBoard();
            int row, col;
            Game.choosePoint(row,col);
            if(Game.gameBoard[row][col] == -1){
                Game.endGamePrint();
                cout << "----------------- That was a bomb! -----------------\n";
                cout << "-----------------     YOU LOSE     -----------------\n";
                endGame = true;
            }
            else{
                Game.updateUserBoard(row, col);
                Game.printUserBoard();
                if(Game.winConditon() && !endGame){
                    Game.endGamePrint();
                    cout << "-----------------     YOU WIN      -----------------\n\n\n";
                    endGame = true;
                }
            }
        }while(!endGame);

        string playAgain;
        cout << "Would you like to play again? (Y/N): ";
        cin >> playAgain;
        if(playAgain == "Y" || playAgain == "y" || playAgain == "YES" || playAgain == "Yes" || playAgain == "yes") continue;
        else exitProgram = true;

    }while(!exitProgram);
}

int difficultySelection(){
    int difficulty;
    bool validInput = false;
    while(!validInput){            // Input validation
        cout << "Select difficulty:\n";
        cout << " -- (1) Beginner\t--\n";
        cout << " -- (2) Intermediate\t--\n";
        cout << " -- (3) Expert\t\t--\n";
        cout << " -- (4) Custom Game\t--\n";
        cout << "Enter choice: ";
        cin >> difficulty;
        if(cin.fail() || difficulty < 1 || difficulty > 4){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "\n\tInvalid Input\n\n";
        }
        else validInput = true;
    }
    return difficulty;
}