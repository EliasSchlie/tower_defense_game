#include "AI.h"
#include <cstdlib>

AI::AI() {
    wave = 1;
    enemiesSpawnedThisWave = 0;
    enemyHealth = 3;
    for (int i = 0; i < GRID_SIZE; i++)
        columnWeights[i] = 10;
}

bool AI::shouldSpawn() const {
    return enemiesSpawnedThisWave < 10;
}

void AI::updateColumnWeight(int col, bool reachedCastle) {
    if (reachedCastle) {
        columnWeights[col] += 3;
    } else {
        columnWeights[col] -= 2;
        if (columnWeights[col] < 1)
            columnWeights[col] = 1;
    }
}

int AI::getSpawnColumn(Grid& grid) {
    int totalWeight = 0;
    for (int c = 0; c < GRID_SIZE; c++) {
        if (grid.getCell(0, c) == Cell::EMPTY)
            totalWeight += columnWeights[c];
    }
    
    if (totalWeight == 0) {
        for (int c = 0; c < GRID_SIZE; c++)
            if (grid.getCell(0, c) == Cell::EMPTY)
                return c;
        return 0;
    }
    
    int pick = rand() % totalWeight;
    int cumulative = 0;
    for (int c = 0; c < GRID_SIZE; c++) {
        if (grid.getCell(0, c) != Cell::EMPTY) continue;
        cumulative += columnWeights[c];
        if (pick < cumulative)
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
