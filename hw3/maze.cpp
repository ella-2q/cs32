/*  If the start location is equal to the ending location, then we've
 solved the maze, so return true.
Mark the start location as visited.
For each of the four directions,
 If the location one step in that direction (from the start location)
         has no wall and is unvisited,
     then if calling pathExists starting from that location (and
                 ending at the same ending location as in the current
                 call) returns true,
              then return true.
Return false.
 */

bool pathExists(char maze[][10], int sr, int sc, int er, int ec){
    // Return true if there is a path from (sr,sc) to (er,ec)
    // through the maze; return false otherwise
    
    if (sr == er && sc == ec) return true;
    
    maze[sr][sc] = '&';
    
    // SOUTH
    
    if (maze[sr + 1][sc] != '&' && maze[sr + 1][sc] != 'X'){
        if (pathExists(maze, sr + 1, sc, er, ec)) {
            return true;
        }
    }
    
    // NORTH
    if (maze[sr - 1][sc] != '&' && maze[sr - 1][sc] != 'X'){
        if (pathExists(maze, sr - 1, sc, er, ec)) {
            return true;
        }
    }
    
    // EAST
    if (maze[sr][sc + 1] != '&' && maze[sr][sc + 1] != 'X'){
        if (pathExists(maze, sr, sc + 1, er, ec)) {
            return true;
        }
    }
    
    // WEST
    if (maze[sr][sc - 1] != '&' && maze[sr][sc - 1] != 'X'){
        if (pathExists(maze, sr, sc - 1, er, ec)) {
            return true;
        }
    }
    
    return false;
    
    
    }

/*
int main()
{
    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X' },
        { 'X','.','.','.','.','X','.','.','X','X' },
        { 'X','.','X','X','X','.','X','.','.','X' },
        { 'X','X','X','X','X','.','X','X','.','X' },
        { 'X','.','X','X','X','.','X','X','X','X' },
        { 'X','.','X','.','.','.','X','.','.','X' },
        { 'X','.','.','.','X','.','X','.','.','X' },
        { 'X','X','X','X','X','.','X','.','X','X' },
        { 'X','.','.','.','.','.','.','.','.','X' },
        { 'X','X','X','X','X','X','X','X','X','X' }
    };

    if (pathExists(maze, 3,5, 8,8))
        std::cout << "Solvable!" << std::endl;
    else
        std::cout << "Out of luck!" << std::endl;

}
*/
