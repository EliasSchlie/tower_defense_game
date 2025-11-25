#ifndef AI_H
#define AI_H

#include "Grid.h"
#include "Tower.h"
#include "Enemy.h"
#include <vector>

class AI {
public:
    AI();
    bool shouldSpawn() const;
    Enemy spawnEnemy(Grid& grid);
    void nextWave(int playerScore);
    void findBestSpawnColumns(Grid& grid, std::vector<Tower>& towers);
    bool allWavesComplete() const;
    int getWave() const;
    int getEnemiesSpawnedThisWave() const;
    int getEnemyHealth() const;

private:
    int wave;
    int enemiesSpawnedThisWave;
    int enemyHealth;
    std::vector<int> bestSpawnColumns;
    int getSpawnColumn(Grid& grid);
};

#endif

