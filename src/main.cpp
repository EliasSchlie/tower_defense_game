#include "Grid.h"
#include "Castle.h"

int main() {
    Grid grid;
    Castle castle;
    
    grid.setCell(castle.getRow(), castle.getCol(), Cell::CASTLE);
    
    grid.display();
    return 0;
}

