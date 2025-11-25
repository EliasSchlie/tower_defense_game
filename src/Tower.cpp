#include "Tower.h"

Tower::Tower(int r, int c) {
    row = r;
    col = c;
}

int Tower::getRow() const { return row; }
int Tower::getCol() const { return col; }

