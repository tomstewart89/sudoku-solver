#include "SudokuSolver.h"
#include <fstream>

int main(int argc, char **argv)
{
    int grid[9][9], *put = (int*)grid;
    ifstream strm;

    // We accept only one command line argument, the filename of the .csv or .txt for the unsolved grid
    if(argc != 2)
    {
        cout << "Error: invalid number of arguments, just specify the filename for the unsolved grid\n";
        return 1;
    }

    strm.open(argv[1]);

    // If the name was invalid then stop
    if(!strm.is_open())
    {
        cout << "Error: couldn't open file\n";
        return 1;
    }

    // We'll just step through the specified file and when we come upon a numeral assume its an entry in the grid
    for(char c; !strm.eof(); strm >> c)
        if(c >= '0' &&  c <= '9')
            *put++ = c - '0';

    cout << "\nPuzzle entered was: \n\n";

    Print(grid);

    cout << "\n***working***\n\n";

    Solve(grid);

    cout << "\n***done!***\n\n";

    Print(grid);

    cout << "\nResult was " << (Valid(grid)? "valid" : "not valid") << "\n\n";

    return 0;
}
