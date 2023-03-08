#include <cassert>

#include "Tile.h"

Tile::Tile(int _value, int _status) {
    value = _value;
    status = _status;
}

std::pair <int, int> Tile::getData() {
    return std::make_pair(value, status);
}

bool Tile::isBomb() {
    return value == -1;
}

bool Tile::isEmpty() {
    return value == 0;
}

int Tile::getAdjacentBombs() {
    return value;
}

bool Tile::isVeiled() {
    return status == 0;
}

bool Tile::isMarked() {
    return status == 1;
}

bool Tile::isOpened() {
    return status == 2;
}

void Tile::mark() {
    status = 1;
}

void Tile::unmark() {
    status = 0;
}

void Tile::open() {
    status = 2;
}