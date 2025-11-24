#ifndef CASTLE_H
#define CASTLE_H

class Castle {
public:
    Castle();
    void takeDamage(int amount);
    int getHealth() const;
    bool isDestroyed() const;
    int getRow() const;
    int getCol() const;

private:
    int health;
    int row;
    int col;
};

#endif

