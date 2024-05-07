#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"

class Board {
private:
    int width;
    int height;
    int numMines;
    int revealedCount;
    int safeTiles;
    int totalSize;
    Tile* tiles;

    void placeMines(int firstX, int firstY);
    void updateCounts();
    bool isValid(int x, int y) const; 
    void revealFinalBoard();
    
public:
    Board(int w, int h, int mines);
    ~Board();
    void display() const;
    bool tileReveal(int x, int y);
    bool gameOver() const; 
    bool gameWon() const; 
    
};

#endif