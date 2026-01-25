#include "Life.h"
#include <iostream>
#include <fstream>
using namespace std;

Life::Life(int rows, int cols)
{
    if (rows < 1)
        rows = 1;
    if (cols < 1)
        cols = 1;
    if (rows > MAXROW)
        rows = MAXROW;
    if (cols > MAXCOL)
        cols = MAXCOL;

    maxrow = rows;
    maxcol = cols;

    for (int r = 0; r < MAXROW; r++)
        for (int c = 0; c < MAXCOL; c++)
            grid[r][c] = 0;
}

int Life::neighbor_count(int row, int col)
/*
Pre:  The Life object contains a configuration, and the coordinates
      row and col define a cell inside its hedge.
Post: The number of living neighbors of the specified cell is returned.
*/
{
    int count = 0;

    int row_lower = (row == 0) ? row : row - 1;
    int row_upper = (row == maxrow - 1) ? row : row + 1;
    int col_lower = (col == 0) ? col : col - 1;
    int col_upper = (col == maxcol - 1) ? col : col + 1;

    for (int i = row_lower; i <= row_upper; i++)
        for (int j = col_lower; j <= col_upper; j++)
            count += grid[i][j];

    count -= grid[row][col];
    return count;
}

void Life::update()
/*
Pre:  The Life object contains a configuration.
Post: The Life object contains the next generation of configuration.
*/
{
    int row, col;
    int new_grid[MAXROW][MAXCOL];

    for (row = 0; row < maxrow; row++)
        for (col = 0; col < maxcol; col++)
            switch (neighbor_count(row, col))
            {
            case 2:
                new_grid[row][col] = grid[row][col]; //  Status stays the same.
                break;
            case 3:
                new_grid[row][col] = 1; //  Cell is now alive.
                break;
            default:
                new_grid[row][col] = 0; //  Cell is now dead.
            }

    for (row = 0; row < maxrow; row++)
        for (col = 0; col < maxcol; col++)
            grid[row][col] = new_grid[row][col];
}

void Life::instructions()
/*
Pre:  None.
Post: Instructions for using the Life program have been printed.
*/
{
    cout << "Welcome to Conway's game of Life." << endl;
    cout << "This game uses a grid of size "
         << maxrow << " by " << maxcol << " in which" << endl;
    cout << "each cell can either be occupied by an organism or not." << endl;
    cout << "The occupied cells change from generation to generation" << endl;
    cout << "according to the number of neighboring cells which are alive."
         << endl;
}

void Life::initialize()
/*
Pre:  None.
Post: The Life object contains a configuration specified by the user.
*/

{
    int row, col;
    for (row = 0; row < MAXROW; row++)
        for (col = 0; col < MAXCOL; col++)
            grid[row][col] = 0;

    cout << "Would you like to read the initial configuration from a file? (y/n): ";
    string choice;
    getline(cin, choice);
    bool from_file = !choice.empty() && (choice[0] == 'y' || choice[0] == 'Y');

    if (from_file)
    {
        cout << "Enter filename: ";
        string filename;
        getline(cin, filename);
        ifstream infile(filename);
        if (!infile)
        {
            cout << "Could not open file. Falling back to keyboard input." << endl;
            from_file = false;
        }
        else
        {
            string comment;
            getline(infile, comment);
            cout << "Configuration name: " << comment << endl;
            string line;
            for (row = 0; row < maxrow; row++)
            {
                if (!getline(infile, line))
                    line = "";
                for (col = 0; col < maxcol && col < (int)line.length(); col++)
                {
                    if (line[col] == 'x' || line[col] == 'X')
                        grid[row][col] = 1;
                    else
                        grid[row][col] = 0;
                }
                for (; col < maxcol; col++)
                    grid[row][col] = 0;
            }
            infile.close();
            return;
        }
    }

    // Keyboard input fallback or chosen
    cout << "Enter the initial configuration as " << maxrow << " lines of " << maxcol << " characters (x for alive, blank for dead):" << endl;
    string line;
    for (row = 0; row < maxrow; row++)
    {
        getline(cin, line);
        while (line.empty())
            getline(cin, line);
        for (col = 0; col < maxcol && col < (int)line.length(); col++)
        {
            if (line[col] == 'x' || line[col] == 'X')
                grid[row][col] = 1;
            else
                grid[row][col] = 0;
        }
        for (; col < maxcol; col++)
            grid[row][col] = 0;
    }
}

void Life::print()
/*
Pre:  The Life object contains a configuration.
Post: The configuration is written for the user.
*/

{
    int row, col;
    cout << "\nThe current Life configuration is:" << endl;
    for (row = 0; row < maxrow; row++)
    {
        for (col = 0; col < maxcol; col++)
            if (grid[row][col] == 1)
                cout << '*';
            else
                cout << ' ';
        cout << endl;
    }
    cout << endl;
}

void Life::save_to_file(const std::string &filename, const std::string &comment) const
{
    std::ofstream outfile(filename);
    if (!outfile)
    {
        std::cout << "Could not open file for writing." << std::endl;
        return;
    }
    outfile << comment << std::endl;
    for (int row = 0; row < maxrow; row++)
    {
        for (int col = 0; col < maxcol; col++)
        {
            if (grid[row][col] == 1)
                outfile << 'x';
            else
                outfile << ' ';
        }
        outfile << std::endl;
    }
    outfile.close();
    std::cout << "Configuration saved to '" << filename << "'." << std::endl;
}