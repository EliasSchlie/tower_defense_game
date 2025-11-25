#include "Grid.h"
#include "Castle.h"
#include "Tower.h"
#include "TowerPlacement.h"
#include <vector>

int main() {
    Grid grid;
    Castle castle;
    std::vector<Tower> towers;
    
    grid.setCell(castle.getRow(), castle.getCol(), Cell::CASTLE);
    placeTowers(grid, towers);
    
    return 0;
}

