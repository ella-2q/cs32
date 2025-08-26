// Player.cpp

#include "provided.h"
#include <string>
#include <iostream>
using namespace std;


class HumanPlayerImpl
{
  public:
    HumanPlayerImpl(HumanPlayer* p);
    int chooseMove(const Scaffold& s, int N, int color);
  private:
    HumanPlayer* m_player;
};

class BadPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class SmartPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
private:
    int determineBestComputerMove(Scaffold s, int N, int color);
    int determineBestHumanMove(Scaffold s, int N, int color);
    int opponent(int color){
        if (color == RED) return BLACK;
        else return RED;
    }
    bool gameOver(const Scaffold& s, int N, int& winner);
    int ratePosition(const Scaffold&, int N, int color);
    int minimax(Scaffold& s, int N, int color, int depth, bool maxOrMin);
    bool checkDirection(const Scaffold& s, int column, int level, int N, char direction, int color) const;
    
    int m_AIColor;
    const int MAX_DEPTH = 6;
};

struct SmartMove {
    int x;
    int y;
    int score;
};

HumanPlayerImpl::HumanPlayerImpl(HumanPlayer* p)
 : m_player(p)
{}

int HumanPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    cout << "Please enter a valid column: " << endl;
    int choice;
    cin >> choice;
    while (choice < 1 || choice > s.cols() || s.checkerAt(choice, s.levels()) != VACANT){
        cout << "Error: column input not valid. Try again." << endl;
        cin >> choice;
    }
    return choice;
}

int BadPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    for (int i = 1; i <= s.cols(); i++) {
        if (s.checkerAt(i, s.levels()) == VACANT)
            return i;
    }
    return 0;
}

int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    
    m_AIColor = color;
    int bestMove = -1;
    int bestScore = -10000;
    
    // loops through columns, if you cannot make a Move there don't call minimax on the spot. Otherwise call minimax to rate the move and return the score. If the score is better than best score, change it and save the move.
    
    
    for (int col = 1; col <= s.cols(); ++col) {
            Scaffold copy = s;
            if (!copy.makeMove(col, color))
                continue;

            int score = minimax(copy, N, opponent(color), 1, false);
            if (score > bestScore) {
                bestScore = score;
                bestMove = col;
            }
        }
    
    // If no move is ideal, choose the first legal move.
    
        if (bestMove == -1 ) {
            for (int column = 1; column <= s.cols(); ++column) {
                if (s.checkerAt(column, s.levels()) == VACANT) {
                    bestMove = column;
                    break;
                }
            }
        }
    
    return bestMove;
    
}

int SmartPlayerImpl::minimax(Scaffold& s, int N, int color, int depth, bool maxOrMin)
{
    // the base case is if the game is over, the three cases are if the AI wins, the opponent wins or the game is a tie. We subtract 1000 by the depth to look to win in as few moves as possible.
    
    int winner;
    if (gameOver(s, N, winner)) {
        if (winner == TIE_GAME) {
            return 0;
        }
        else if (winner == m_AIColor) {
            return 1000 - depth;
        }
        else {
            return -1000 + depth;
        }
    }
    
    // This is included to make sure the program doesn't stall out. With a basic rating algorithm set up if we exceed a maximum recursion depth.

    if (depth >= MAX_DEPTH) {
        return ratePosition(s, N, m_AIColor);
    }
    
    // impossibly large scores are created to compare too. Using the negative score if the opponent wins, and the positive if the AI wins.
    
    int bestScore;
    if (maxOrMin) {
        bestScore = -2000;
    } else {
        bestScore = 2000;
    }

    
    // for each column in the board, if you cannot make a move right now move to the next column. Otherwise check the minimax value of going down that path. If the outcome there is better than the current one, update bestScore.
    
    for (int col = 1; col <= s.cols(); ++col) {
        if (!s.makeMove(col, color)) {
            continue;
        }

        int score = minimax(s, N, opponent(color), depth + 1, !maxOrMin);
        s.undoMove();

        if (maxOrMin) {
            if (score > bestScore) {
                bestScore = score;
            }
        } else {
            if (score < bestScore) {
                bestScore = score;
            }
        }
    }

    return bestScore;
}


bool SmartPlayerImpl::gameOver(const Scaffold& s, int N, int& winner){
    
    // Loops over every point in the board and uses check direction for each direction to see if a connect N is pressent, changing winner to the correct color if the game is over. Otherwise winner = tie game.
    
    for (int i = 1; i <= s.cols(); i++){
        for (int j = 1; j <= s.levels(); j++){
            int color = s.checkerAt(i, j);
            if (color == VACANT) continue;
            
            if (checkDirection(s, i, j, N, 'H', color) || checkDirection(s, i, j, N, 'V', color) || checkDirection(s, i, j, N, 'U', color) || checkDirection(s, i, j, N, 'D', color)){
                winner = color;

                return true;
            }
        }
    }
    
    if (s.numberEmpty() == 0) {
        winner = TIE_GAME;
        return true;
    }
    
    return false;
}

bool SmartPlayerImpl::checkDirection(const Scaffold& s, int column, int level, int N, char direction, int color) const{
    
    // runs through each direction to check whether there is a connect N in that direction. The same code as used in game to check whether the game is over.
    
    if (direction == 'H'){
        for (int i = 0; i < N; i++){
            int c = column + i;
            int l = level;
            if (c < 1 || c > s.cols() || l < 1 || l > s.levels()) {
                return false;
            }
            if (s.checkerAt(c, l) != color) {
                return false;
            }
        }
        return true;
    } //for horizontal
    
    if (direction == 'V'){
        for (int i = 0; i < N; i++){
            int c = column;
            int l = level + i;
            if (c < 1 || c > s.cols() || l < 1 || l > s.levels()) {
                return false;
            }
            if (s.checkerAt(c, l) != color) {
                return false;
            }
        }
        return true;
    } //for vertical
    
    if (direction == 'U'){
        for (int i = 0; i < N; i++){
            int c = column + i;
            int l = level + i;
            if (c < 1 || c > s.cols() || l < 1 || l > s.levels()) {
                return false;
            }
            if (s.checkerAt(c, l) != color) {
                return false;
            }
        }
        return true;
    } //for diagonal right up
    
    if (direction == 'D'){
        for (int i = 0; i < N; i++){
            int c = column + i;
            int l = level - i;
            if (c < 1 || c > s.cols() || l < 1 || l > s.levels()) {
                return false;
            }
            if (s.checkerAt(c, l) != color) {
                return false;
            }
        }
        return true;
    } //for diagonal right down
    return true;
}

int SmartPlayerImpl::ratePosition(const Scaffold& s, int N, int color)
{
    // code to rate each position, gives 0 initially. It goes through each cell on the board and increases the score for each piece belonging to the player and subtracts a point for all pieces belonging to the opponent. Used if recursion is taking too long.
    
    int score = 0;
    for (int c = 1; c <= s.cols(); ++c) {
        for (int l = 1; l <= s.levels(); ++l) {
            int value = s.checkerAt(c, l);
            if (value == color)
                score += 1;
            else if (value == opponent(color))
                score -= 1;
        }
    }
    return score;
}

//******************** Player derived class functions *************************

//  These functions simply delegate to the Impl classes' functions.  You should
//  not change any of the code from here to the end of this file.

HumanPlayer::HumanPlayer(string nm)
 : Player(nm)
{
    m_impl = new HumanPlayerImpl(this);
}
 
HumanPlayer::~HumanPlayer()
{
    delete m_impl;
}
 
int HumanPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

BadPlayer::BadPlayer(string nm)
 : Player(nm)
{
    m_impl = new BadPlayerImpl;
}
 
BadPlayer::~BadPlayer()
{
    delete m_impl;
}
 
int BadPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

SmartPlayer::SmartPlayer(string nm)
 : Player(nm)
{
    m_impl = new SmartPlayerImpl;
}
 
SmartPlayer::~SmartPlayer()
{
    delete m_impl;
}
 
int SmartPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}
