#include "Tile.h"

Tile::Tile() : isMine(false), revealed(false), value(0){}
bool Tile::hasMine() const {
    return isMine;
}

bool Tile::isCovered()const{
    return !revealed;
}

bool Tile::reveal(){
    if(!revealed){
        revealed = true;
        return !isMine;
    }
    return true;
}

int Tile::getValue() const {
    return value;
}

void Tile::setValue(int newValue){
    value = newValue;
}

void Tile::setMine(bool mine){
    isMine = mine;
}

void Tile::makeRevealed(bool revealed){
    this ->revealed = revealed;
}