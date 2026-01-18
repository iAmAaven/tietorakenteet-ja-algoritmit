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
    int grid[MAXROW][MAXCOL];
    int neighbor_count(int row, int col);
};