#include "Utility.h"
#include "Life.h"
#include <iostream>
#include <sstream>
#include <string>
#include <limits>
#include <thread>
#include <chrono>
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

      cout << "Would you like to run in animation mode? (y/n): ";
      string anim_choice;
      getline(cin, anim_choice);
      bool animation = !anim_choice.empty() && (anim_choice[0] == 'y' || anim_choice[0] == 'Y');

      int delay_ms = 0;
      int num_updates = -1;
      if (animation)
      {
            cout << "Enter delay between updates in milliseconds (e.g., 2000 for 2 seconds): ";
            string delay_str;
            getline(cin, delay_str);
            istringstream dss(delay_str);
            if (!(dss >> delay_ms) || delay_ms < 0)
                  delay_ms = 2000;

            cout << "Enter number of updates to run (leave empty to run until Ctrl-C): ";
            string updates_str;
            getline(cin, updates_str);
            if (!updates_str.empty())
            {
                  istringstream uss(updates_str);
                  if (!(uss >> num_updates) || num_updates < 1)
                        num_updates = -1;
            }
            configuration.print();
            int updates_done = 0;
            while (num_updates < 0 || updates_done < num_updates)
            {
                  std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
                  configuration.update();
                  configuration.print();
                  ++updates_done;
            }
      }
      else
      {
            configuration.print();
            cout << "Continue viewing new generations? " << endl;
            while (user_says_yes())
            {
                  configuration.update();
                  configuration.print();
                  cout << "Continue viewing new generations? " << endl;
            }
      }

      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      cout << "Would you like to save the final configuration to a file? (y/n): ";
      string save_choice;
      getline(cin, save_choice);
      if (!save_choice.empty() && (save_choice[0] == 'y' || save_choice[0] == 'Y'))
      {
            cout << "Enter filename to save: ";
            string outfilename;
            getline(cin, outfilename);
            cout << "Enter a comment for the configuration (or leave empty for default): ";
            string comment;
            getline(cin, comment);
            if (comment.empty())
                  comment = "Saved configuration";
            configuration.save_to_file(outfilename, comment);
      }
      return EXIT_SUCCESS;
}