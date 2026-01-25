#pragma once

#include <string>

const int MAXROW = 20, MAXCOL = 60;

class Life
{
public:
    Life(int rows = MAXROW, int cols = MAXCOL);
    void initialize();
    void instructions();
    void print();
    void update();
    void save_to_file(const std::string &filename, const std::string &comment = "Saved configuration") const;

private:
    int maxrow, maxcol;
    int grid[MAXROW][MAXCOL];
    int neighbor_count(int row, int col);
};