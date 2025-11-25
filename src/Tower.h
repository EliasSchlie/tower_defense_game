#ifndef TOWER_H
#define TOWER_H

class Tower {
public:
    Tower(int r, int c);
    int getRow() const;
    int getCol() const;
    int getLevel() const;
    int getDamage() const;
    int getRange() const;
    void addKill();

private:
    int row;
    int col;
    int kills;
    int level;
};

#endif

