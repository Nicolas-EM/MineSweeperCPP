/*
Author: Nicolas ESPINOSA MOOSER
Date: 22nd Oct 2020
*/

#include <iostream>
using namespace std;

const int size = 10;         // Size * Size 
int numBombs = 50;
bool endGame = false;
int gameBoard[size][size];        // Back-end board
char userBoard[size][size];       // Board visible to player

void printGameBoard(){                          // Print game board for debugging
    cout << "\n  Game Board\n";
    cout << "     ";
    for(int i = 0; i < size; i++) cout << i << "  ";
    cout << "\n\n";
    for(int x = 0; x < size; x++){
        cout << x << "   ";
        for(int y = 0; y < size; y++){
            if(gameBoard[x][y] != -1) cout << " ";
            cout << gameBoard[x][y] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void printUserBoard(){                          // Print user board unfinished
    cout << "  User Board\n";
    cout << "     ";
    for(int i = 0; i < size; i++) cout << i << "  ";
    cout << "\n\n";
    for(int x = 0; x < size; x++){
        cout << x << "    ";
        for(int y = 0; y < size; y++){
            cout << userBoard[x][y] << "  ";
        }
        cout << "\n";
    }
    cout << "\n";
}

bool withinBounds(int x, int y){
    if(x >= size || x < 0 || y >= size || y < 0) return false;
    else return true;
}

int numOfNearbyBombs(int x, int y){
    if(gameBoard[x][y] == -1) return -1;
    int nearbyBombs = 0;
    for(int i = -1; i < 2; i++){
        for(int j = -1; j < 2; j++){
            if((j == 0 && i == 0) || !withinBounds(x+i,y+j)) continue;
            if(gameBoard[x+i][y+j] == -1){
                nearbyBombs++;
            } 
        }
    }
    return nearbyBombs;
}

void initBoards(){
    for(int x = 0; x < size; x++){              // "Zero out" boards
        for(int y = 0; y < size; y++){
            gameBoard[x][y] = 0;
            userBoard[x][y] = '-';
        }
    }
    int bombsPlaced = 0;                        // Place bombs
    while(bombsPlaced < numBombs){
        int x = rand()%size;
        int y = rand()%size;
        if(gameBoard[x][y] != -1){
            gameBoard[x][y] = -1;
            bombsPlaced++;
        }
    }
    for(int x = 0; x < size; x++){              // Add number of nearby bombs to game board
        for(int y = 0; y < size; y++){
            gameBoard[x][y] = numOfNearbyBombs(x,y);
        }
    }
}

void updateUserBoard(int x, int y){
    // cout << "x = " << x << ", y = " << y << "\n";
    if(!withinBounds(x,y)) return;
    else if(userBoard[x][y] != '-') return;
    else if(gameBoard[x][y] != -1) userBoard[x][y] = char(gameBoard[x][y] + 48);
    if(withinBounds(x+1,y) && userBoard[x+1][y] == '-' && gameBoard[x+1][y] != -1) updateUserBoard(x+1, y);    // Bottom box
    if(withinBounds(x,y+1) && userBoard[x][y+1] == '-' && gameBoard[x][y+1] != -1) updateUserBoard(x, y+1);    // Right box
    if(withinBounds(x-1,y) && userBoard[x-1][y] == '-' && gameBoard[x-1][y] != -1) updateUserBoard(x-1, y);    // Top box
    if(withinBounds(x,y-1) && userBoard[x][y-1] == '-' && gameBoard[x][y+1] != -1) updateUserBoard(x, y-1);    // Left box
}

bool winConditon(){
    for(int x = 0; x < size; x++){
        for(int y = 0; y < size; y++){
            if(userBoard[x][y] == '-' && gameBoard[x][y] != -1) return false;
        }
    }
    return true;
}

void endGamePrint(){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(gameBoard[i][j] == -1) userBoard[i][j] = '*';
            else userBoard[i][j] = int(gameBoard[i][j] + 48);
        }
    }
    printUserBoard();
}

int main(){
    srand(time(0));
    initBoards();
    cout << "Choose number of bombs (Default 50): ";
    cin >> numBombs;
    while(!endGame){
        // printGameBoard();
        printUserBoard();
        if(winConditon()){
            endGamePrint();
            cout << "-----------------     YOU WIN      -----------------\n\n\n";
            endGame = true;
        }
        else{
            cout << "Choose 2 numbers between 0 and " << size - 1 << "\n";
            int x, y;
            cin >> x >> y;
            if(x >= size || x < 0 || y >= size || y < 0){
                cout << "Invalid input. Please try again\n\n";
            }
            else if(gameBoard[x][y] == -1){
                endGamePrint();
                cout << "----------------- That was a bomb! -----------------\n";
                cout << "-----------------     YOU LOSE     -----------------\n";
                endGame = true;
            }
            else{
                updateUserBoard(x,y);
            }
            cout << "\n----------------------------------------------------\n\n";
        }
        
    }
    return 0;
}