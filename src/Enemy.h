#ifndef ENEMY_H
#define ENEMY_H

class Grid;

class Enemy {
public:
    Enemy(int col, int hp = 3);
    int getRow() const;
    int getCol() const;
    int getHealth() const;
    int getSpeed() const;
    void takeDamage(int amount);
    bool isDead() const;
    void move(Grid& grid);

private:
    int row;
    int col;
    int health;
    int speed;
};

#endif

