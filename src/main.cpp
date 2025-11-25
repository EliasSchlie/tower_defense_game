#include "Grid.h"
#include "Castle.h"
#include "Tower.h"
#include <iostream>
#include <vector>

void placeTowers(Grid& grid, std::vector<Tower>& towers) {
    while (towers.size() < 5) {
        grid.display();
        std::cout << "Place up to 5 towers. Enter row and column (e.g., 10 5).\n";
        std::cout << "Rules: Row must be 2-18, cannot place on castle.\n";
        std::cout << "Enter -1 -1 to finish placing towers.\n";
        std::cout << "\nTower " << towers.size() + 1 << "/5 - Enter row col: ";
        
        int row, col;
        std::cin >> row >> col;
        
        if (row == -1 && col == -1) break;
        
        if (row < 2 || row >= GRID_SIZE - 1 || col < 0 || col >= GRID_SIZE) {
            std::cout << "Invalid! Row must be 2-18, col must be 0-19.\n";
            continue;
        }
        if (grid.getCell(row, col) != Cell::EMPTY) {
            std::cout << "Cell is already occupied!\n";
            continue;
        }
        
        towers.push_back(Tower(row, col));
        grid.setCell(row, col, Cell::TOWER);
    }
    grid.display();
    std::cout << towers.size() << " towers placed. Ready to start!\n";
}

int main() {
    Grid grid;
    Castle castle;
    std::vector<Tower> towers;
    
    grid.setCell(castle.getRow(), castle.getCol(), Cell::CASTLE);
    placeTowers(grid, towers);
    
    return 0;
}

