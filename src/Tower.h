#ifndef TOWER_H
#define TOWER_H

class Tower {
public:
    Tower(int r, int c);
    int getRow() const;
    int getCol() const;

private:
    int row;
    int col;
};

#endif

