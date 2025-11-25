#include "Tower.h"

Tower::Tower(int r, int c) {
    row = r;
    col = c;
    kills = 0;
    level = 0;
}

int Tower::getRow() const { return row; }
int Tower::getCol() const { return col; }
int Tower::getLevel() const { return level; }

int Tower::getDamage() const {
    if (level >= 1) return 2;
    return 1;
}

int Tower::getRange() const {
    if (level >= 2) return 3;
    return 2;
}

void Tower::addKill() {
    kills++;
    if (kills >= 6 && level < 2)
        level = 2;
    else if (kills >= 3 && level < 1)
        level = 1;
}
