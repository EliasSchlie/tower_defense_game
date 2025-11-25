#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Game::Game() {
    turn = 0;
    enemiesDestroyed = 0;
    score = 0;
    srand(time(0));
    grid.setCell(castle.getRow(), castle.getCol(), Cell::CASTLE);
}

void Game::run() {
    placeTowers();
    
    while (!gameOver()) {
        turn++;
        moveEnemies();
        spawnEnemy();
        towerAttack();
        display();
        std::cout << "Press Enter...";
        std::cin.get();
        
        if (waveOver() && ai.getWave() < 5) {
            ai.nextWave(score);
            display();
            std::cout << "Wave " << ai.getWave() << " starting! Enemy HP: " << ai.getEnemyHealth() << "\n";
            std::cout << "Press Enter...";
            std::cin.get();
        }
    }
    
    display();
    std::cout << "\nGAME OVER\n";
    std::cout << "Player Score: " << score << "\n";
    std::cout << "Enemies Destroyed: " << enemiesDestroyed << "\n";
    std::cout << "Castle Health: " << castle.getHealth() << "\n";
    std::cout << "Winner: " << (castle.getHealth() > 0 ? "Player" : "AI") << "\n";
}

void Game::placeTowers() {
    std::string errorMsg = "";
    
    while (towers.size() < 5) {
        grid.display();
        std::cout << "Place up to 5 towers. Enter row and column (e.g., 10 5).\n";
        std::cout << "Rules: Row 2-19, col 0-19, not on occupied cells.\n";
        std::cout << "Enter -1 -1 to finish placing towers.\n";
        if (errorMsg != "") std::cout << "Error: " << errorMsg << "\n";
        std::cout << "\nTower " << towers.size() + 1 << "/5 - Enter row col: ";
        errorMsg = "";
        
        int row, col;
        std::cin >> row >> col;
        
        if (row == -1 && col == -1) break;
        
        if (row < 2 || row >= GRID_SIZE || col < 0 || col >= GRID_SIZE) {
            errorMsg = "Invalid! Row must be 2-19, col must be 0-19.";
            continue;
        }
        if (grid.getCell(row, col) != Cell::EMPTY) {
            errorMsg = "Cell is already occupied!";
            continue;
        }
        
        towers.push_back(Tower(row, col));
        grid.setCell(row, col, Cell::TOWER);
    }
    std::cin.ignore();
}

void Game::spawnEnemy() {
    if (!ai.shouldSpawn()) return;
    enemies.push_back(ai.spawnEnemy(grid));
}

void Game::moveEnemies() {
    for (int i = 0; i < enemies.size(); i++) {
        if (enemies[i].isDead()) continue;
        
        for (int s = 0; s < enemies[i].getSpeed(); s++) {
            enemies[i].move(grid);
            
            if (enemies[i].getRow() >= GRID_SIZE - 1) {
                castle.takeDamage(10);
                ai.updateColumnWeight(enemies[i].getSpawnCol(), true);
                enemies[i].takeDamage(999);
                int r = enemies[i].getRow();
                int c = enemies[i].getCol();
                if (!(r == castle.getRow() && c == castle.getCol()))
                    grid.setCell(r, c, Cell::EMPTY);
                break;
            }
        }
    }
}

void Game::towerAttack() {
    for (int t = 0; t < towers.size(); t++) {
        int tr = towers[t].getRow();
        int tc = towers[t].getCol();
        int range = towers[t].getRange();
        int damage = towers[t].getDamage();
        int oldLevel = towers[t].getLevel();
        
        for (int e = 0; e < enemies.size(); e++) {
            if (enemies[e].isDead()) continue;
            
            int er = enemies[e].getRow();
            int ec = enemies[e].getCol();
            
            int rowDist = tr - er;
            int colDist = tc - ec;
            if (rowDist < 0) rowDist = -rowDist;
            if (colDist < 0) colDist = -colDist;
            
            if (rowDist <= range && colDist <= range) {
                enemies[e].takeDamage(damage);
                if (enemies[e].isDead()) {
                    grid.setCell(er, ec, Cell::EMPTY);
                    if (er < GRID_SIZE - 1) {
                        ai.updateColumnWeight(enemies[e].getSpawnCol(), false);
                        towers[t].addKill();
                        if (towers[t].getLevel() != oldLevel) {
                            if (towers[t].getLevel() == 1)
                                grid.setCell(tr, tc, Cell::TOWER_L1);
                            else if (towers[t].getLevel() == 2)
                                grid.setCell(tr, tc, Cell::TOWER_L2);
                            oldLevel = towers[t].getLevel();
                        }
                        enemiesDestroyed++;
                        score += 10;
                    }
                }
                break;
            }
        }
    }
}

void Game::display() {
    grid.display();
    std::cout << "Wave: " << ai.getWave() << "/5 | Turn: " << turn << "\n";
    std::cout << "Enemies Destroyed: " << enemiesDestroyed;
    std::cout << " | Score: " << score;
    std::cout << " | Castle Health: " << castle.getHealth() << "\n";
}

bool Game::waveOver() {
    if (ai.shouldSpawn()) return false;
    for (int i = 0; i < enemies.size(); i++)
        if (!enemies[i].isDead()) return false;
    return true;
}

bool Game::gameOver() {
    if (castle.getHealth() <= 0) return true;
    if (ai.getWave() >= 5 && waveOver()) return true;
    return false;
}
