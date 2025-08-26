#include <queue>
#include <string>
#include <iostream>

using namespace std;

class Coord
       {
         public:
           Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
           int r() const { return m_r; }
           int c() const { return m_c; }
         private:
           int m_r;
           int m_c;
       };


bool pathExists(char maze[][10], int sr, int sc, int er, int ec){
    // Return true if there is a path from (sr,sc) to (er,ec)
    // through the maze; return false otherwise
    queue<Coord> coordQ;
    int counter = 0;
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            if (maze[i][j] == 'X') {
                counter++;
            }
        }
    }
    
    if (counter == 0){
        cerr << "Maze has no walls, true" << endl;
        return true;
    }
    
    char seen = '%';
    
    Coord current(sr, sc);
    coordQ.push(current);
    maze[sr][sc] = seen;
    counter = 0;
    
    while (!coordQ.empty()){
        current = coordQ.front();   // look at top item in the stack
        coordQ.pop();
        counter++;
        cerr << "Coord " << counter << ": (" << current.r() << ", " << current.c() << ")" << endl;
        
        int  y = current.r();
        int x = current.c();
        
        // debugging through maze print.
        cerr << "LOADING...." << endl;
        for (int i = 0; i < 10; i++){
            for (int j = 0; j < 10; j++){
                cerr << maze[i][j];
            }
            cerr << endl;
        }
        cerr << endl;
        
        // check condition
        if (y == er && x == ec){ //If the current (r,c) coordinate is equal to the ending coordinate, then we've solved the maze so return true!
            return true;
        }
        
        // SOUTH
        if (y + 1 < 10){
            if (maze[y + 1][x] != seen && maze[y + 1][x] != 'X'){
                Coord push = Coord(y + 1 , x);
                coordQ.push(push);
                maze[y + 1][x] = seen;
            }
        }
        // WEST
        if (x - 1 >= 0){
            if (maze[y][x - 1] != seen && maze[y][x - 1] != 'X'){
                Coord push = Coord(y, x - 1);
                coordQ.push(push);
                maze[y][x - 1] = seen;
            }
        }

        // NORTH
        if (y - 1 >= 0){
            if (maze[y - 1][x] != seen && maze[y - 1][x] != 'X'){
                Coord push = Coord(y - 1, x);
                coordQ.push(push);
                maze[y - 1][x] = seen;
            }
        }
        
        // EAST
        if (x + 1 < 10){
            if (maze[y][x + 1] != seen && maze[y][x + 1] != 'X'){
                Coord push = Coord(y, x + 1);
                coordQ.push(push);
                maze[y][x + 1] = seen;
            }
        }
    }
    
    return false;
}


int main() {
    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X' },
        { 'X','.','.','.','.','X','.','.','X','X' },
        { 'X','.','X','X','.','X','X','.','.','X' },
        { 'X','X','X','.','.','.','.','X','.','X' },
        { 'X','.','X','X','X','.','X','X','X','X' },
        { 'X','.','X','.','.','.','X','.','.','X' },
        { 'X','.','.','.','X','.','X','.','.','X' },
        { 'X','X','X','X','X','.','X','.','X','X' },
        { 'X','.','.','.','.','.','.','.','.','X' },
        { 'X','X','X','X','X','X','X','X','X','X' }
    };

    if (pathExists(maze, 3,5, 8,8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}
