#ifndef TILE_H
#define TILE_H

class Tile {
private:
    bool isMine;
    bool revealed;
    int value;

public:
    Tile();
    bool hasMine() const;
    bool isCovered() const;
    bool reveal(); 
    int getValue() const;
    void setValue(int newValue);
    void setMine(bool mine);
    void makeRevealed(bool revealed);
};

#endif