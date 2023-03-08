#ifndef TILE_H
#define TILE_H

#include <tuple>

struct Tile {
private:
    int value; // -1 = bomb, 0 - 8 = number of adjacent bombs
    int status; // 0 = veiled, 1 = marked, 2 = opened

public:
    Tile(int, int);
    std::pair <int, int> getData();
    bool isBomb();
    bool isEmpty();
    int getAdjacentBombs();
    bool isVeiled();
    bool isMarked();
    bool isOpened();
    void mark();
    void unmark();
    void open();
};

#endif