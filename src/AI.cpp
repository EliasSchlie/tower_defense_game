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

void AI::findBestSpawnColumns(Grid& grid, std::vector<Tower>& towers) {
    int towerInfluence[GRID_SIZE];
    for (int i = 0; i < GRID_SIZE; i++)
        towerInfluence[i] = 0;
    
    for (int t = 0; t < towers.size(); t++) {
        int tc = towers[t].getCol();
        for (int offset = -2; offset <= 2; offset++) {
            int col = tc + offset;
            if (col >= 0 && col < GRID_SIZE)
                towerInfluence[col]++;
        }
    }
    
    int minInfluence = 10000;
    bestSpawnColumns.clear();
    
    for (int c = 0; c < GRID_SIZE; c++) {
        if (towerInfluence[c] < minInfluence) {
            minInfluence = towerInfluence[c];
            bestSpawnColumns.clear();
            bestSpawnColumns.push_back(c);
        } 
        else if (towerInfluence[c] == minInfluence) {
            bestSpawnColumns.push_back(c);
        }
    }
}

int AI::getSpawnColumn(Grid& grid) {
    if (bestSpawnColumns.size() > 0) {
        int startIdx = rand() % bestSpawnColumns.size();
        for (int i = 0; i < bestSpawnColumns.size(); i++) {
            int idx = (startIdx + i);
            if (idx >= bestSpawnColumns.size()) {
                idx -= bestSpawnColumns.size();
            }
            if (grid.getCell(0, bestSpawnColumns[idx]) == Cell::EMPTY)
                return bestSpawnColumns[idx];
        }
    }
    
    int startCol = rand() % GRID_SIZE;
    for (int i = 0; i < GRID_SIZE; i++) {
        int c = (startCol + i) % GRID_SIZE;
        if (grid.getCell(0, c) == Cell::EMPTY)
            return c;
    }
    return 0;
}

Enemy AI::spawnEnemy(Grid& grid) {
    int col = getSpawnColumn(grid);
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
