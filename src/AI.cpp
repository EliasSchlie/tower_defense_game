#include "AI.h"
#include <cstdlib>

AI::AI() {
    wave = 1;
    enemiesSpawnedThisWave = 0;
    enemyHealth = 3;
}

bool AI::shouldSpawn() const {
    return enemiesSpawnedThisWave < 10;
}

int AI::getSpawnColumn(Grid& grid, std::vector<Tower>& towers) {
    int bestCol = -1;
    int maxDist = -1;
    
    for (int c = 0; c < GRID_SIZE; c++) {
        if (grid.getCell(0, c) != Cell::EMPTY) continue;
        
        int minTowerDist = GRID_SIZE;
        for (int t = 0; t < towers.size(); t++) {
            int dist = towers[t].getCol() - c;
            if (dist < 0) dist = -dist;
            if (dist < minTowerDist) minTowerDist = dist;
        }
        
        if (minTowerDist >= 3 && minTowerDist > maxDist) {
            maxDist = minTowerDist;
            bestCol = c;
        }
    }
    
    if (bestCol != -1) return bestCol;
    
    int col;
    int attempts = 0;
    do {
        col = rand() % GRID_SIZE;
        attempts++;
    } while (grid.getCell(0, col) != Cell::EMPTY && attempts < 100);
    return col;
}

Enemy AI::spawnEnemy(Grid& grid, std::vector<Tower>& towers) {
    int col = getSpawnColumn(grid, towers);
    grid.setCell(0, col, Cell::ENEMY);
    enemiesSpawnedThisWave++;
    return Enemy(col, enemyHealth);
}

void AI::nextWave(int playerScore) {
    if (wave >= 5) return;
    
    wave++;
    enemiesSpawnedThisWave = 0;
    
    if (playerScore >= (wave - 1) * 80)
        enemyHealth++;
}

bool AI::allWavesComplete() const {
    return wave >= 5 && enemiesSpawnedThisWave >= 10;
}

int AI::getWave() const { return wave; }
int AI::getEnemiesSpawnedThisWave() const { return enemiesSpawnedThisWave; }
int AI::getEnemyHealth() const { return enemyHealth; }

