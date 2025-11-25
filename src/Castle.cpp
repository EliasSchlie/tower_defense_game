#include "Castle.h"
#include "Grid.h"

Castle::Castle() {
    health = 100;
    row = GRID_SIZE - 1;
    col = GRID_SIZE / 2;
}

void Castle::takeDamage(int amount) {
    health -= amount;
}

int Castle::getHealth() const { return health; }
bool Castle::isDestroyed() const { return health <= 0; }
int Castle::getRow() const { return row; }
int Castle::getCol() const { return col; }

