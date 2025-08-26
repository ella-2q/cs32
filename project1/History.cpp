#include "History.h"
#include <iostream>
using namespace std;
/*
 PRIVATE MEMBERS ========
 int m_rows;
 int m_columns;
 char m_room[MAXROWS][MAXCOLS];
 */

History::History(int nRows, int nCols){
    m_rows = nRows;
    m_columns = nCols;
    for (int i = 0; i < m_rows; i++){
        for (int j = 0; j < m_columns; j++){
            m_room[i][j] = '.';
        }
    }
}

bool History::record(int r, int c){
    r--;
    c--;
    if ((r < m_rows) && r >= 0 && c < m_columns && c >= 0){
        if (m_room[r][c] == '.'){
            m_room[r][c] = 'A';
        }
        else{
            m_room[r][c]++;
        }
        return true;
    }
    else return false;
}


void History::display() const{
    // Draw the grid
    clearScreen();
    for (int r = 0; r < m_rows; r++)
    {
        for (int c = 0; c < m_columns; c++)
            cout << m_room[r][c];
        cout << '\n';
    }
    cout << endl;
}
