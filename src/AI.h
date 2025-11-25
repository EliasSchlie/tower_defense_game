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
    void updateColumnWeight(int col, bool reachedCastle);
    bool allWavesComplete() const;
    int getWave() const;
    int getEnemiesSpawnedThisWave() const;
    int getEnemyHealth() const;

private:
    int wave;
    int enemiesSpawnedThisWave;
    int enemyHealth;
    int columnWeights[20];
    int getSpawnColumn(Grid& grid);
};

#endif

