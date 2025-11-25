#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Game::Game() {
    turn = 0;
    enemiesSpawned = 0;
    enemiesDestroyed = 0;
    score = 0;
    maxEnemies = 10;
    srand(time(0));  // Seeds random number generator
    grid.setCell(castle.getRow(), castle.getCol(), Cell::CASTLE);
}

void Game::run() {
    placeTowers();
    
    while (!isOver()) {
        turn++;
        spawnEnemy();
        moveEnemies();
        display();
        std::cout << "Press Enter...";
        std::cin.get();
    }
    
    display();
    std::cout << "\n=== GAME OVER ===\n";
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
    if (enemiesSpawned >= maxEnemies) return;
    
    int col = rand() % GRID_SIZE;
    if (grid.getCell(0, col) == Cell::EMPTY) {
        enemies.push_back(Enemy(col));
        grid.setCell(0, col, Cell::ENEMY);
        enemiesSpawned++;
    }
}

void Game::moveEnemies() {
    for (int i = 0; i < enemies.size(); i++) {
        if (enemies[i].isDead()) continue;
        
        enemies[i].move(grid);
        
        if (enemies[i].getRow() >= GRID_SIZE - 1) {
            castle.takeDamage(10);
            enemies[i].takeDamage(999);
            int r = enemies[i].getRow();
            int c = enemies[i].getCol();
            if (!(r == castle.getRow() && c == castle.getCol()))
                grid.setCell(r, c, Cell::EMPTY);
        }
    }
}

void Game::display() {
    grid.display();
    std::cout << "Turn: " << turn << " | Castle HP: " << castle.getHealth();
    std::cout << " | Score: " << score;
    std::cout << " | Enemies: " << enemiesSpawned << "/" << maxEnemies << "\n";
}

bool Game::isOver() {
    if (castle.getHealth() <= 0) return true;
    
    if (enemiesSpawned >= maxEnemies) {
        for (int i = 0; i < enemies.size(); i++)
            if (!enemies[i].isDead()) return false;
        return true;
    }
    return false;
}

