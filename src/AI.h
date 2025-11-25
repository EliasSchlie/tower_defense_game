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
    Enemy spawnEnemy(Grid& grid, std::vector<Tower>& towers);
    void nextWave(int playerScore);
    bool allWavesComplete() const;
    int getWave() const;
    int getEnemiesSpawnedThisWave() const;
    int getEnemyHealth() const;

private:
    int wave;
    int enemiesSpawnedThisWave;
    int enemyHealth;
    int getSpawnColumn(Grid& grid, std::vector<Tower>& towers);
};

#endif

