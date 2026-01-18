#pragma once

const int MAXROW = 20, MAXCOL = 60;

class Life
{
public:
    Life(int rows = MAXROW, int cols = MAXCOL);
    void initialize();
    void instructions();
    void print();
    void update();

private:
    int maxrow, maxcol;
    int grid[MAXROW + 2][MAXCOL + 2]; // allows for two extra rows and columns
    int neighbor_count(int row, int col);
};