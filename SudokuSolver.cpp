#include "SudokuSolver.h"

bool Solve(int grid[9][9], int index)
{
    static int it = 0;

    // If we've reached the end of the grid, then success!
    if(index > 80)
        return true;

    // If the index has already been assigned a value then no need to fill it, just attempt to solve it and move on
    if(((int*)grid)[index])
        return Solve(grid, index + 1);

    // For all the available digits, find the first one that isn't definitely wrong and proceed making that assumption.
    for(int digit = 1; digit < 10; digit++)
    {
        static int row, column, blockStart;

        row = index / 9;
        column = index % 9;
        blockStart = row / 3 * 27 +  column / 3 * 3;

        // Iterate through 10 indexes
        int i;
        for(i = 0; i < 9; i++)
        {
            // Check if the row contains the number
            if(grid[row][i] == digit)
                break;

            // Check if the column contains the number
            if(grid[i][column] == digit)
                break;

            // Check if the block contains the number
            if(((int*)grid)[blockStart + i / 3 * 9 + i % 3] == digit)
                break;
        }

        // If the digit wasn't found in any elements in the row column or block
        if(i == 9)
            ((int*)grid)[index] = digit;
        else
            continue;

        // Then try to solve the remaining cells based on that choice
        if(Solve(grid, index + 1))
            return true;
        // Otherwise unmake the choice and try again which in this case means doing nothing
        else
            ((int*)grid)[index] = 0;
    }

    // If none of the options worked then we failed to solve the puzzle
    return false;
}

void Print(int grid[9][9])
{
    // Print the top line
    cout << "+-----------------------+\n";

    // Print the grid
    for(int i = 0; i < 81; i++)
    {
        // If we're at the third column the write a divider
        if(!(i % 3))
            cout << "| ";

        // If we're at the third row the write a divider
        if(!(i % 9) && i)
        {
            if(!(i % 27))
                cout << "\n|-------+-------+-------|\n| ";
            else
                cout << "\n| ";
        }

        // Write the element
        cout << ((int*)grid)[i] << ' ';
    }

    // The bottom line
    cout << "|\n+-----------------------+\n";

    cout.flush();
}

bool Valid(int grid[9][9])
{
    int *grid1d = (int*)grid;
    int row, column, blockStart;
    int *rowCheck, *columnCheck, *blockCheck;

    // For every cell in the grid
    for(int i = 0; i < 81; i++)
    {
        // This means we can check if so far a grid is valid since blank cells are assigned 0
        if(grid1d[i] == 0)
            continue;

        row = i / 9;
        column = i % 9;
        blockStart = row / 3 * 27 +  column / 3 * 3;

        // Iterate through 10 indexes
        for(int j = 0; j < 9; j++)
        {
            // Check if the row contains the number
            rowCheck = grid1d + row * 9 + j;
            if(grid1d[i] == *rowCheck && (grid1d + i) != rowCheck)
                return false;

            // Check if the row contains the number
            columnCheck = grid1d + j * 9 + column;
            if(grid1d[i] == *columnCheck && (grid1d + i) != columnCheck)
                return false;

            // Check if the row contains the number
            blockCheck = grid1d + blockStart + j / 3 * 9 + j % 3;
            if(grid1d[i] == *blockCheck && (grid1d + i) != blockCheck)
                return false;
        }
    }

    return true;
}

