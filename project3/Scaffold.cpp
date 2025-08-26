// Scaffold.cpp

#include "provided.h"
#include <utility>
#include <iostream>
#include <vector>
#include <stack>


using namespace std;

class ScaffoldImpl
{
  public:
    ScaffoldImpl(int nColumns, int nLevels); 
    int cols() const;
    int levels() const;
    int numberEmpty() const;
    int checkerAt(int column, int level) const; 
    void display() const; 
    bool makeMove(int column, int color); 
    int undoMove();
private:
    int mcolumns;
    int mlevels;
    vector<vector<int>> grid;
    
    int emptyCount;
    
    stack<int> historyColumns;
    stack<int> historyLevels;
};

ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels)
{
    if (nColumns <= 0 || nLevels <= 0){
        cerr << "Columns/Levels were not positive." << endl;
        terminate();
    }
    mcolumns = nColumns;
    mlevels = nLevels;
    emptyCount = mcolumns*mlevels;
    
    grid.resize(mcolumns, vector<int>(mlevels, VACANT));
}

int ScaffoldImpl::cols() const
{
    return mcolumns;
}

int ScaffoldImpl::levels() const
{
    return mlevels;
}

int ScaffoldImpl::numberEmpty() const
{
    return emptyCount;
}

int ScaffoldImpl::checkerAt(int column, int level) const
{
    if (column < 1 || column > mcolumns || level < 1 || level > mlevels) {
        return VACANT;
    }
    
    int result = grid[column-1][level-1];
    if (result == RED)  {return RED;}
    if (result == BLACK)  {return BLACK;}
    return VACANT;
}

void ScaffoldImpl::display() const
{
    for (int i = mlevels - 1; i >= 0; i--){
        for (int j = 0; j < mcolumns; j++){
            cout << "|";
            if (grid[j][i] == VACANT) cout << " ";
            else if (grid[j][i] == RED) cout << "R";
            else if (grid[j][i] == BLACK) cout << "B";
        }
        cout << "|";
        cout << endl;
    }
    for (int j = 0; j < mcolumns*2 + 1; j++){
        if (j%2 == 0) cout << "+";
        else cout << "-";
    }
    cout << endl;
}

bool ScaffoldImpl::makeMove(int column, int color)
{
    
    
    if (column > mcolumns || column <= 0) return false;
    for (int i = 0; i < mlevels; i++){
        if (checkerAt(column, i + 1) == VACANT){
            grid[column-1][i] = color;
            historyColumns.push(column - 1);
            historyLevels.push(i);
            emptyCount--;
            return true;
        }
    }
    return false;
}

int ScaffoldImpl::undoMove()
{
    if (historyLevels.empty()) return 0;

    int oldC = historyColumns.top();
    historyColumns.pop();
    int oldL = historyLevels.top();
    historyLevels.pop();
    
    grid[oldC][oldL] = VACANT;
    emptyCount++;
    return oldC + 1;
}

//******************** Scaffold functions *******************************

//  These functions simply delegate to ScaffoldImpl's functions.  You should
//  not change any of the code from here to the end of this file.

Scaffold::Scaffold(int nColumns, int nLevels)
{
    m_impl = new ScaffoldImpl(nColumns, nLevels);
}
 
Scaffold::~Scaffold()
{
    delete m_impl;
}
 
Scaffold::Scaffold(const Scaffold& other)
{
    m_impl = new ScaffoldImpl(*other.m_impl);
}
 
Scaffold& Scaffold::operator=(const Scaffold& rhs)
{
    if (this != &rhs)
    {
        Scaffold temp(rhs);
        swap(m_impl, temp.m_impl);
    }
    return *this;
}
 
int Scaffold::cols() const
{
    return m_impl->cols();
}

int Scaffold::levels() const
{
    return m_impl->levels();
}

int Scaffold::numberEmpty() const
{
    return m_impl->numberEmpty();
}

int Scaffold::checkerAt(int column, int level) const
{
    return m_impl->checkerAt(column, level);
}
 
void Scaffold::display() const
{
    m_impl->display();
}
 
bool Scaffold::makeMove(int column, int color)
{
    return m_impl->makeMove(column, color);
}
 
int Scaffold::undoMove()
{
    return m_impl->undoMove();
}
