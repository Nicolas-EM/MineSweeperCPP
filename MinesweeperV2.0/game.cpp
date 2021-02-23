#include "game.h"
using namespace std;

game::game(const int difficulty){
    switch(difficulty){
        case 1:
            numOfRows = numOfCols = 9;
            numOfBombs = 10;
            break;
        case 2:
            numOfRows = numOfCols = 16;
            numOfBombs = 40;
            break;
        case 3:
            numOfRows = 16;
            numOfCols = 30;
            numOfBombs = 99;
            break;
        case 4:
            {
                bool validInput = false;
                while (!validInput){
                    cout << "Enter numOfRows: ";
                    cin >> numOfRows;
                    if (cin.fail() || numOfRows < 1 || numOfRows > 99){
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "\n\tInvalid Input\n\n";
                    }
                    else  validInput = true;
                }
                validInput = false;
                while (!validInput){
                    cout << "Enter numOfCols: ";
                    cin >> numOfCols;
                    if (cin.fail() || numOfCols < 1 || numOfCols > 99){
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "\n\tInvalid Input\n\n";
                    }
                    else validInput = true;
                }
                validInput = false;
                while (!validInput){
                    cout << "Enter the number of bombs: ";
                    cin >> numOfBombs;
                    if (cin.fail() || numOfRows < 1 || numOfRows > 50){
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "\n\tInvalid Input\n\n";
                    }
                    else validInput = true;
                }
                break;
            }
        default:
            throw "Error in setting difficulty\n";
            break;
    }

    // Init boards
    userBoard.resize(numOfRows, vector<char>(numOfCols, '-'));
    gameBoard.resize(numOfRows, vector<int>(numOfCols, 0));
}

bool game::withinBounds(const int xPos, const int yPos){
    if(xPos < 0 || xPos > numOfCols-1 || yPos < 0 || yPos > numOfRows-1) return false;
    else return true;
}

int game::numOfNearbyBombs(const int xPos, const int yPos){
    if(gameBoard[xPos][yPos] == -1) return -1;
    int nearbyBombs = 0;
    for(int i = -1; i < 2; i++){
        for(int j = -1; j < 2; j++){
            if((i == 0 && j == 0) || !withinBounds(xPos+i,yPos+j)) continue;
            if(gameBoard[xPos+i][yPos+j] == -1){
                nearbyBombs++;
            } 
        }
    }
    return nearbyBombs;
}

void game::generateBoard(){
    srand(time(nullptr));
    printUserBoard();
    int row, col, bombsPlaced = 0;
    while(true){
        std::cout << "Enter position (Row Column): ";
        std::cin >> row >> col;
        if(cin.fail() || !withinBounds(row,col)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "\n\tInvalid Input\n";
            cout << "\tRange of X is [0, " << numOfRows << "] and range of Y is [0, " << numOfCols << "]\n\n";
        }
        else break;
    }

    while(bombsPlaced < numOfBombs){
        int rowBomb, colBomb;
        do{
            rowBomb = rand()%numOfRows;
        }while(rowBomb == row);
        do{
            colBomb = rand()%numOfCols;
        }while(colBomb == col);
        if(gameBoard[rowBomb][colBomb] == -1) continue;
        else{
            gameBoard[rowBomb][colBomb] = -1;
            bombsPlaced++;
        }
    }

    for(int row = 0; row < numOfRows; row++){
        for(int col = 0; col < numOfCols; col++){
            gameBoard[row][col] = numOfNearbyBombs(row,col);
        }
    }
    updateUserBoard(row, col);
}

void game::printGameBoard(){      
    cout << "Printing GAME board\n";
    for(vector<vector<int>>::const_iterator row = gameBoard.begin(); row != gameBoard.end(); row++){
        for(vector<int>::const_iterator col = row->begin(); col != row->end(); col++){
            if(*col != -1) cout << " ";
            cout << *col << " ";
        }
        cout << "\n";
    }
}

void game::printUserBoard(){
    for(int i = 0; i < 52; i++) cout << "=";
    cout << "\nPrinting User board\n";
    for(vector<vector<char>>::const_iterator row = userBoard.begin(); row != userBoard.end(); row++){
        for(vector<char>::const_iterator col = row->begin(); col != row->end(); col++){
            cout << *col << " ";
        }
        cout << "\n";
    }
    for(int i = 0; i < 52; i++) cout << "=";
    cout << "\n";
}

void game::choosePoint(int &row, int &col){
    bool validInput = false;
    while(!validInput){
        cout << "Enter position (Row Column): ";
        cin >> row >> col;
        if(cin.fail() || !withinBounds(row,col)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "\n\tInvalid Input\n";
            cout << "\tRange of X is [0, " << numOfRows << "] and range of Y is [0, " << numOfCols << "]\n\n";
        }
        else validInput = true;
    }
}

void game::updateUserBoard(const int xPos, const int yPos){
    if(!withinBounds(xPos,yPos)) return;
    else if(userBoard[xPos][yPos] != '-' || gameBoard[xPos][yPos] == -1) return;
    else if(gameBoard[xPos][yPos] != -1) userBoard[xPos][yPos] = char(gameBoard[xPos][yPos] + 48);
    if(withinBounds(xPos+1,yPos) && userBoard[xPos+1][yPos] == '-' && gameBoard[xPos+1][yPos] != -1) updateUserBoard(xPos+1, yPos);    // Bottom box
    if(withinBounds(xPos,yPos+1) && userBoard[xPos][yPos+1] == '-' && gameBoard[xPos][yPos+1] != -1) updateUserBoard(xPos, yPos+1);    // Right box
    if(withinBounds(xPos-1,yPos) && userBoard[xPos-1][yPos] == '-' && gameBoard[xPos-1][yPos] != -1) updateUserBoard(xPos-1, yPos);    // Top box
    if(withinBounds(xPos,yPos-1) && userBoard[xPos][yPos-1] == '-' && gameBoard[xPos][yPos-1] != -1) updateUserBoard(xPos, yPos-1);    // Left box
}

void game::endGamePrint(){
    for(int i = 0; i < numOfRows; i++){
        for(int j = 0; j < numOfCols; j++){
            if(gameBoard[i][j] == -1) userBoard[i][j] = '*';
            else userBoard[i][j] = int(gameBoard[i][j] + 48);
        }
    }
    printUserBoard();
}

bool game::winConditon(){
    for(int x = 0; x < numOfRows; x++){
        for(int y = 0; y < numOfCols; y++){
            if(userBoard[x][y] == '-' && gameBoard[x][y] != -1) return false;
        }
    }
    return true;
}