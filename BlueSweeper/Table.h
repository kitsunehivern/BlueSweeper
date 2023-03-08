#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <vector>

#include "Tile.h"

struct Table {
private:
    int numRow, numCol, numBomb;
    std::vector <std::vector <Tile> > tiles;
    int specialX, specialY;
    bool firstOpen;
    std::vector <std::vector <Tile> > lastTiles;

public:
    Table();
    Table(int, int, int);
    void inputData(std::istream&);
    void outputData(std::ostream&);
    int getNumRow();
    int getNumCol();
    int getNumBomb();
    int getNumMarked();
    bool isBomb(int, int);
    bool isEmpty(int, int);
    bool isSpecial(int, int);
    int getAdjacentBombs(int, int);
    bool isVeiled(int, int);
    bool isMarked(int, int);
    bool isOpened(int, int);
    void setUp(int, int);
    void mark(int, int);
    void open(int, int, bool check = true);
    int gameState();
    void refresh();
    void undo();
};

#endif