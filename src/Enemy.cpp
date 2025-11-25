#include "Enemy.h"
#include "Grid.h"

Enemy::Enemy(int c, int hp) {
    row = 0;
    col = c;
    health = hp;
}

int Enemy::getRow() const { return row; }
int Enemy::getCol() const { return col; }
int Enemy::getHealth() const { return health; }
bool Enemy::isDead() const { return health <= 0; }

void Enemy::takeDamage(int amount) {
    health -= amount;
}

void Enemy::move(Grid& grid) {
    if (row >= GRID_SIZE - 1) return;  // Already at bottom
    
    int newRow = row + 1;
    int newCol = col;
    
    if (grid.getCell(newRow, col) == Cell::EMPTY || grid.getCell(newRow, col) == Cell::CASTLE) {
        // Can move down
    }
    else if (col > 0 && grid.getCell(newRow, col - 1) == Cell::EMPTY) {
        newCol = col - 1;
    }
    else if (col < GRID_SIZE - 1 && grid.getCell(newRow, col + 1) == Cell::EMPTY) {
        newCol = col + 1;
    }
    else {
        return;
    }
    
    // Update grid
    grid.setCell(row, col, Cell::EMPTY);
    row = newRow;
    col = newCol;
    if (grid.getCell(row, col) != Cell::CASTLE)
        grid.setCell(row, col, Cell::ENEMY);
}

