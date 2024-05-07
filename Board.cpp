#include "Board.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Board::Board(int w, int h, int mines) : width(w), height(h), numMines(mines), revealedCount(0) , safeTiles((w*h) - mines), totalSize(w*h){
    
    tiles = new Tile[totalSize];
    for (int i = 0; i < totalSize; ++i){
        tiles[i].setValue(0);
        tiles[i].makeRevealed(false);
    }
    placeMines(0, 0);
    updateCounts();
}

Board::~Board(){
    delete[] tiles;
}

void Board::placeMines(int firstx, int firsty){
    srand(time(nullptr));

    int minesPlaced = 0;
    while (minesPlaced < numMines){
        int randIndex = rand()% totalSize;
        int randx = randIndex % width;
        int randy = randIndex / width;

        if(randx != firstx || randy != firsty){
            if(!tiles[randIndex].hasMine()){
                tiles[randIndex].setMine(true);
                minesPlaced++;
            }
        }
    }
}
void Board::updateCounts() {
   for (int i = 0; i < totalSize; ++i) {
        if (!tiles[i].hasMine()) {
            int count = 0;
            int row = i / width;
            int col = i % width;

            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    int nx = row + dx;
                    int ny = col + dy;

                    if (nx >= 0 && nx < height && ny >= 0 && ny < width && tiles[nx * width + ny].hasMine()) {
                        ++count;
                        }
                }
            }
            tiles[i].setValue(count);
        }
    }
}
void Board::display() const {
    std::cout << "    ";
    for (int i = 0; i < width; ++i) {
        std::cout << i << "   ";
    }
    std::cout << std::endl;
    std::cout << "  |---";
    for (int i = 1; i < width; ++i) {
        std::cout << "|---";
    }
    std::cout << "|" << std::endl;

    for (int i = 0; i < height; ++i) {
        std::cout << i << " | ";
        for (int j = 0; j < width; ++j) {
            int index = i * width + j;
            if (!gameOver() && tiles[index].isCovered()) {
                std::cout << "#";
            } else {
                if (tiles[index].hasMine()) {
                    std::cout << "M";
                } else {
                    std::cout << tiles[index].getValue();
                }
            }
            std::cout << " | ";
        }
        std::cout << std::endl;

        if (i < height - 1) {
            std::cout << "  |---";
            for (int k = 1; k < width; ++k) {
                std::cout << "|---";
            }
            std::cout << "|" << std::endl;
        }
    }

    std::cout << "  |---";
    for (int i = 1; i < width; ++i) {
        std::cout << "|---";
    }
    std::cout << "|" << std::endl;
}


bool Board::tileReveal(int x, int y) {
    if (!isValid(x, y)) {
        return true; 
    }
    if (!tiles[x * width + y].isCovered()){
        return true;
    }
    if (tiles[x * width + y].hasMine()) {
        revealFinalBoard(); 
        return false;
    }

    if (!tiles[x * width + y].reveal()) {
        return false;
    }
    
    revealedCount++;

    if (revealedCount == safeTiles) {
        return false; 
    }

    return true; 
}
bool Board::gameOver() const {
    for(int i = 0; i < totalSize; ++i){
        if(!tiles[i].isCovered() && tiles[i].hasMine()){
            return true;
        }
    }
    return false;
}

bool Board::gameWon() const {
    return revealedCount == safeTiles; 
}

bool Board::isValid(int x, int y) const {
    return x >= 0 && x < height && y >= 0 && y < width;
}

void Board::revealFinalBoard() {
    for (int i = 0; i < totalSize; ++i) {
        tiles[i].makeRevealed(true);
    }
}