//
// Created by alon on 5/20/24.
//

#ifndef CPP_EX3_24_MAIN_BOARD_H
#define CPP_EX3_24_MAIN_BOARD_H
#include <string.h>
#include "Resources.h" //todo: pay attention for loop include!

#define UpEdge 0
#define UpRightEdge 1
#define UpLeftEdge 2
#define DownEdge 3
#define DownRightEdge 4
#define DownLeftEdge 5

#define UpVertex 0
#define UpRightVertex 1
#define UpLeftVertex 2
#define DownRightVertex 3
#define DownLeftVertex 4
#define DownVertex 5

#define SETTLEMENT 2
#define CITY 1

class Tile{ //todo: add ports?
private:
    bool isSea;
    int number;
    std::string resource;
    Tile & [] neighbors;
    UrbanEntity & [] UrbanEntities;
    Road & [] roads;
private:
    Settlement& removeSettlement(Settlement& settlement);
public:
    Tile(int dieNum, std::string resource ,issea= false);
    void UpdateNeighbor(Tile & neighbor);
    void placeUrbanEntity(UrbanEntity& UrbanEntity);
    void placeRoad(Road& road);

};

class Board {
private:
    Tile&[] tiles;
public:
    board();
    void printBoard();
};



#endif //CPP_EX3_24_MAIN_BOARD_H
