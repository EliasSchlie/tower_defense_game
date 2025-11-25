#include "Grid.h"
#include <iostream>

Grid::Grid() {
    for (int r = 0; r < GRID_SIZE; r++)
        for (int c = 0; c < GRID_SIZE; c++)
            cells[r][c] = Cell::EMPTY;
}

void Grid::setCell(int row, int col, Cell type) {
    cells[row][col] = type;
}

Cell Grid::getCell(int row, int col) const {
    return cells[row][col];
}

void Grid::display() const {
    for (int r = 0; r < GRID_SIZE; r++) {
        for (int c = 0; c < GRID_SIZE; c++) {
            switch (cells[r][c]) {
                case Cell::EMPTY:  std::cout << "▢ "; break;
                case Cell::CASTLE: std::cout << "🏰"; break;
                case Cell::TOWER:  std::cout << "🔫"; break;
                case Cell::ENEMY:  std::cout << "👾"; break;
            }
        }
        std::cout << '\n';
    }
}

