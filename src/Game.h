#ifndef GAME_H
#define GAME_H

#include "Grid.h"
#include "Castle.h"
#include "Tower.h"
#include "Enemy.h"
#include <vector>

class Game {
public:
    Game();
    void run();

private:
    Grid grid;
    Castle castle;
    std::vector<Tower> towers;
    std::vector<Enemy> enemies;
    int turn;
    int enemiesSpawned;
    int enemiesDestroyed;
    int score;
    int maxEnemies;
    
    void placeTowers();
    void spawnEnemy();
    void moveEnemies();
    void display();
    bool isOver();
};

#endif

