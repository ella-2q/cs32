// Game.cpp

#include "provided.h"
#include <stack>
#include <iostream>

using namespace std;

class GameImpl
{
  public:
    GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black); 
    bool completed(int& winner) const; 
    bool takeTurn(); 
    void play(); 
    int checkerAt(int c, int r) const;
    bool checkDirection(int column, int level, int N, char direction, int color) const;
    
private:
    Scaffold scaffold;
    int numberRow;
    int turn;
    Player* red;
    Player *black;
};


GameImpl::GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black) : scaffold(nColumns, nLevels), numberRow(N), turn(0), red(red), black(black)
{}

bool GameImpl::completed(int& winner) const
{
    for (int i = 1; i <= scaffold.cols(); i++){
        for (int j = 1; j <= scaffold.levels(); j++){
            int color = scaffold.checkerAt(i, j);
            if (color == VACANT) continue;
            
            if (checkDirection(i, j, numberRow, 'H', color) || checkDirection(i, j, numberRow, 'V', color) || checkDirection(i, j, numberRow, 'U', color) || checkDirection(i, j, numberRow, 'D', color)){
                winner = color;
                return true;
            }
        }
    }
    
    if (scaffold.numberEmpty() == 0) {
        winner = TIE_GAME;
        return true;
    }
    
    return false;
}

bool GameImpl::checkDirection(int column, int level, int N, char direction, int color) const{
    int count = 0;
    
    if (direction == 'H'){
        for (int i = 0; i < N; i++){
            int c = column + i;
            int l = level;
            if (c < 1 || c > scaffold.cols() || l < 1 || l > scaffold.levels()) {
                return false;
            }
            if (scaffold.checkerAt(c, l) != color) {
                return false;
            }
        }
        count++;
    } //for horizontal
    
    if (direction == 'V'){
        for (int i = 0; i < N; i++){
            int c = column;
            int l = level + i;
            if (c < 1 || c > scaffold.cols() || l < 1 || l > scaffold.levels()) {
                return false;
            }
            if (scaffold.checkerAt(c, l) != color) {
                return false;
            }
        }
        count++;
    } //for vertical
    
    if (direction == 'U'){
        for (int i = 0; i < N; i++){
            int c = column + i;
            int l = level + i;
            if (c < 1 || c > scaffold.cols() || l < 1 || l > scaffold.levels()) {
                return false;
            }
            if (scaffold.checkerAt(c, l) != color) {
                return false;
            }
        }
        count++;
    } //for diagonal right up
    
    if (direction == 'D'){
        for (int i = 0; i < N; i++){
            int c = column + i;
            int l = level - i;
            if (c < 1 || c > scaffold.cols() || l < 1 || l > scaffold.levels()) {
                return false;
            }
            if (scaffold.checkerAt(c, l) != color) {
                return false;
            }
        }
    } //for diagonal right down
    
    return true;
}

bool GameImpl::takeTurn()
{
    int winner;
    if (completed(winner)) return false;
    
    if (turn == 0){
        int move = red->chooseMove(scaffold, numberRow, RED);
        scaffold.makeMove(move, RED);
        turn++;
        return true;
    }
    else {
        int move = black->chooseMove(scaffold, numberRow, BLACK);
        scaffold.makeMove(move, BLACK);
        turn--;
        return true;
    }
   
}

void GameImpl::play()
{
    int winner;
    if (red->isInteractive() || black->isInteractive()){
        scaffold.display();
        while (completed(winner) != true){
            takeTurn();
            scaffold.display();
            if (completed(winner) != true){
                takeTurn();
                scaffold.display();
            }
        }
        if (winner == BLACK) cout << "Black has won the game!" << endl;
        else if (winner == RED) cout << "Red has won the game!" << endl;
        else if (winner == TIE_GAME) cout << "There was a tie!" << endl;
        return;
    }
    
    else {
        scaffold.display();
        cout << endl;
        while (completed(winner) != true){
            takeTurn();
            if (completed(winner) != true) takeTurn();
            scaffold.display();
            if (completed(winner) != true){
                cout << "Press ENTER to continue...";
                cin.ignore(10000, '\n'); // wait for ENTER
            }
        }
        if (winner == BLACK) cout << "Black has won the game!" << endl;
        else if (winner == RED) cout << "Red has won the game!" << endl;
        else if (winner == TIE_GAME) cout << "There was a tie!" << endl;
        return;
    }
}

int GameImpl::checkerAt(int c, int r) const
{
    if (scaffold.checkerAt(c, r) == RED) return RED;
    else if (scaffold.checkerAt(c, r) == BLACK) return BLACK;
    return VACANT;
} 

//******************** Game functions **************************************

//  These functions simply delegate to GameImpl's functions.  You should not
//  change any of the code from here to the end of this file.

Game::Game(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    m_impl = new GameImpl(nColumns, nLevels, N, red, black);
}
 
Game::~Game()
{
    delete m_impl;
}
 
bool Game::completed(int& winner) const
{
    return m_impl->completed(winner);
}

bool Game::takeTurn()
{
    return m_impl->takeTurn();
}

void Game::play()
{
    m_impl->play();
}
 
int Game::checkerAt(int c, int r) const
{
    return m_impl->checkerAt(c, r);
}
