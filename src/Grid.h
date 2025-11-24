#ifndef GRID_H
#define GRID_H

const int GRID_SIZE = 20;

enum class Cell { EMPTY, CASTLE, TOWER, ENEMY };

class Grid {
public:
    Grid();
    void display() const;
    void setCell(int row, int col, Cell type);
    
private:
    Cell cells[GRID_SIZE][GRID_SIZE];
};

#endif

