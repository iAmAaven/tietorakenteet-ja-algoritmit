#include "Utility.h"
#include "Life.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() // Program to play Conway's game of Life.
/*
Pre:  The user supplies an initial configuration of living cells.
Post: The program prints a sequence of pictures showing the changes in
      the configuration of living cells according to the rules for
      the game of Life.
Uses: The class Life and its methods initialize(), print(), and update().
      The functions  instructions(),  user_says_yes().
*/
{
      int rows = MAXROW;
      int cols = MAXCOL;
      string line;

      cout << "Enter the desired size of the grid (rows cols, leave empty for 20x60):" << endl;
      getline(cin, line);
      if (!line.empty())
      {
            istringstream in(line);
            if (in >> rows >> cols)
            {
                  if (rows < 1)
                        rows = 1;
                  if (cols < 1)
                        cols = 1;
                  if (rows > MAXROW)
                        rows = MAXROW;
                  if (cols > MAXCOL)
                        cols = MAXCOL;
            }
            else
            {
                  rows = MAXROW;
                  cols = MAXCOL;
            }
      }

      Life configuration(rows, cols);

      configuration.instructions();
      configuration.initialize();
      configuration.print();
      cout << "Continue viewing new generations? " << endl;
      while (user_says_yes())
      {
            configuration.update();
            configuration.print();
            cout << "Continue viewing new generations? " << endl;
      }

      return EXIT_SUCCESS;
}