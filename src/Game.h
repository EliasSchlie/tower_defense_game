#ifndef GAME_H
#define GAME_H

#include "Grid.h"
#include "Castle.h"
#include "Tower.h"
#include "Enemy.h"
#include "AI.h"
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
    AI ai;
    int turn;
    int enemiesDestroyed;
    int score;
    
    void placeTowers();
    void spawnEnemy();
    void moveEnemies();
    void towerAttack();
    void display();
    bool waveOver();
    bool gameOver();
};

#endif

