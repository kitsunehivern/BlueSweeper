#include <queue>
#include <cassert>
#include <tuple>

#include "Table.h"
#include "Random.h"

Table::Table() {
    numRow = numCol = numBomb = 0;
    tiles.clear();
    specialX = specialY = -1;
    firstOpen = true;
}

Table::Table(int _numRow, int _numCol, int _numBomb) {
    numRow = _numRow;
    numCol = _numCol;
    numBomb = _numBomb;
    tiles.assign(numRow, std::vector <Tile> (numCol, Tile(0, 0)));
    specialX = specialY = -1;
    firstOpen = true;

    std::vector <std::pair <int, int> > allSpecial;
    for (int posX = 0; posX < numRow; posX++) {
        for (int posY = 0; posY < numCol; posY++) {
            int adjacentTiles = 0;
            for (int deltaX : {-1, 0, 1}) {
                for (int deltaY : {-1, 0, 1}) {
                    if (deltaX == 0 && deltaY == 0) {
                        continue;
                    }

                    int newX = posX + deltaX;
                    int newY = posY + deltaY;

                    if (0 > newX || newX >= numRow || 0 > newY || newY >= numCol) {
                        continue;
                    }

                    adjacentTiles++;
                }
            }

            if (numRow * numCol - adjacentTiles - 2 >= numBomb) {
                allSpecial.push_back(std::make_pair(posX, posY));
            }
        }
    }

    if (!allSpecial.empty()) {
        int idx = randInt(0, allSpecial.size() - 1);
        specialX = allSpecial[idx].first;
        specialY = allSpecial[idx].second;
        tiles[specialX][specialY] = Tile(9, 0);
    }

    for (int ithBomb = 1; ithBomb <= numBomb; ithBomb++) {
        int posX, posY;
        bool check;
        do {
            posX = randInt(0, numRow - 1);
            posY = randInt(0, numCol - 1);

            check = !isBomb(posX, posY);
            if (specialX != -1 && specialY != -1) {
                check &= (abs(posX - specialX) > 1 || abs(posY - specialY) > 1);
            }

        } while (!check);

        tiles[posX][posY] = Tile(-1, 0);
    }
}

void Table::inputData(std::istream &stream) {
    stream >> numRow >> numCol >> numBomb;
    tiles.assign(numRow, std::vector <Tile> (numCol, Tile(0, 0)));
    for (int posX = 0; posX < numRow; posX++) {
        for (int posY = 0; posY < numCol; posY++) {
            int value, status;
            stream >> value >> status;

            tiles[posX][posY] = Tile(value, status);

            if (status == 2) {
                firstOpen = false;
            }
        }
    }

    stream >> specialX >> specialY;
}

void Table::outputData(std::ostream &stream) {
    stream << numRow << " " << numCol << " " << numBomb << "\n";
    for (int posX = 0; posX < numRow; posX++) {
        for (int posY = 0; posY < numCol; posY++) {
            int value, status;
            std::tie(value, status) = tiles[posX][posY].getData();

            stream << value << " " << status << "\t\n"[posY == numCol - 1];
        }
    }

    stream << specialX << " " << specialY << "\n";
}

int Table::getNumRow() {
    return numRow;
}

int Table::getNumCol() {
    return numCol;
}

int Table::getNumBomb() {
    return numBomb;
}

int Table::getNumMarked() {
    int res = 0;
    for (int posX = 0; posX < numRow; posX++) {
        for (int posY = 0; posY < numCol; posY++) {
            res += isMarked(posX, posY);
        }
    }

    return res;
}

bool Table::isBomb(int x, int y) {
    return tiles[x][y].isBomb();
}

bool Table::isEmpty(int x, int y) {
    return tiles[x][y].isEmpty();
}

bool Table::isSpecial(int x, int y) {
    return x == specialX && y == specialY;
}

int Table::getAdjacentBombs(int x, int y) {
    return tiles[x][y].getAdjacentBombs();
}

bool Table::isVeiled(int x, int y) {
    return tiles[x][y].isVeiled();
}

bool Table::isMarked(int x, int y) {
    return tiles[x][y].isMarked();
}

bool Table::isOpened(int x, int y) {
    return tiles[x][y].isOpened();
}

void Table::setUp(int firstOpenX, int firstOpenY) {
    if (isBomb(firstOpenX, firstOpenY)) {
        int posX, posY;
        bool check;
        do {
            posX = randInt(0, numRow - 1);
            posY = randInt(0, numCol - 1);

            check = !isBomb(posX, posY) && (posX != firstOpenX || posY != firstOpenY);
            if (specialX != -1 && specialY != -1) {
                check &= (abs(posX - specialX) > 1 || abs(posY - specialY) > 1);
            }

        } while (!check);

        tiles[firstOpenX][firstOpenY] = Tile(0, 0);
        tiles[posX][posY] = Tile(-1, isMarked(posX, posY));
    }

    for (int posX = 0; posX < numRow; posX++) {
        for (int posY = 0; posY < numCol; posY++) {
            if (isBomb(posX, posY)) {
                continue;
            }

            int adjacentBombs = 0;
            for (int deltaX : {-1, 0, 1}) {
                for (int deltaY : {-1, 0, 1}) {
                    if (deltaX == 0 && deltaY == 0) {
                        continue;
                    }

                    int newX = posX + deltaX;
                    int newY = posY + deltaY;

                    if (0 > newX || newX >= numRow || 0 > newY || newY >= numCol) {
                        continue;
                    }

                    adjacentBombs += isBomb(newX, newY);
                }
            }

            tiles[posX][posY] = Tile(adjacentBombs, isMarked(posX, posY));
        }
    }

    open(firstOpenX, firstOpenY);
}

void Table::mark(int x, int y) {
    if (isOpened(x, y)) {
        return;
    }

    lastTiles = tiles;
    
    if (isMarked(x, y)) {
        tiles[x][y].unmark();
    } else {
        tiles[x][y].mark();
    }
}

void Table::open(int x, int y, bool check) {
    if (check) {
        lastTiles = tiles;
    }

    if (firstOpen) {
        firstOpen = false;
        setUp(x, y);
        return;
    }

    if (isVeiled(x, y)) {
        tiles[x][y].open();

        if (isBomb(x, y)) {
            for (int posX = 0; posX < numRow; posX++) {
                for (int posY = 0; posY < numCol; posY++) {
                    if (isBomb(posX, posY) && !isMarked(posX, posY)) {
                        tiles[posX][posY].open();
                    }
                }
            }

            return;
        }
        
        if (isEmpty(x, y)) {
            std::queue <std::pair <int, int> > que;
            que.push(std::make_pair(x, y));

            while (!que.empty()) {
                int curX = que.front().first, curY = que.front().second;
                que.pop();

                if (!isEmpty(curX, curY)) {
                    continue;
                }

                for (int deltaX : {-1, 0, 1}) {
                    for (int deltaY : {-1, 0, 1}) {
                        if (deltaX == 0 && deltaY == 0) {
                            continue;
                        }

                        int newX = curX + deltaX;
                        int newY = curY + deltaY;

                        if (0 > newX || newX >= numRow || 0 > newY || newY >= numCol) {
                            continue;
                        }

                        if (!isOpened(newX, newY) && !isBomb(newX, newY)) {
                            tiles[newX][newY].open();
                            que.push(std::make_pair(newX, newY));
                        }
                    }
                }
            }
        }

        bool check = true;
        for (int posX = 0; posX < numRow; posX++) {
            for (int posY = 0; posY < numCol; posY++) {
                if (!isBomb(posX, posY) && !isOpened(posX, posY)) {
                    check = false;
                    break;
                }
            }
        }

        if (check) {
            for (int posX = 0; posX < numRow; posX++) {
                for (int posY = 0; posY < numCol; posY++) {
                    if (isBomb(posX, posY) && isVeiled(posX, posY)) {
                        tiles[posX][posY].mark();
                    }
                }
            }
        }

        if (!isEmpty(x, y)) {
            return;
        }
    }

    if (!check) {
        return;
    }
    
    if (isOpened(x, y)) {
        assert(!isBomb(x, y));

        if (!isEmpty(x, y)) {
            int adjacentMarked = 0;
            for (int deltaX : {-1, 0, 1}) {
                for (int deltaY : {-1, 0, 1}) {
                    if (deltaX == 0 && deltaY == 0) {
                        continue;
                    }

                    int newX = x + deltaX;
                    int newY = y + deltaY;

                    if (0 > newX || newX >= numRow || 0 > newY || newY >= numCol) {
                        continue;
                    }

                    adjacentMarked += isMarked(newX, newY);
                }
            }
            
            if (getAdjacentBombs(x, y) == adjacentMarked) {
                for (int deltaX : {-1, 0, 1}) {
                    for (int deltaY : {-1, 0, 1}) {
                        if (deltaX == 0 && deltaY == 0) {
                            continue;
                        }

                        int newX = x + deltaX;
                        int newY = y + deltaY;

                        if (0 > newX || newX >= numRow || 0 > newY || newY >= numCol) {
                            continue;
                        }

                        open(newX, newY, false);
                    }
                }
            }
        }
    }
}

int Table::gameState() {
    bool isWinState = true;
    for (int posX = 0; posX < numRow; posX++) {
        for (int posY = 0; posY < numCol; posY++) {
            if (isBomb(posX, posY)) {
                if (isOpened(posX, posY)) {
                    return -1;
                }
            } else {
                isWinState &= isOpened(posX, posY);
            }
        }
    }

    return isWinState;
}

void Table::refresh() {
    *this = Table(numRow, numCol, numBomb);
}

void Table::undo() {
    tiles = lastTiles;
}