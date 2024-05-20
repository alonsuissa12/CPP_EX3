// 211344015 alonsuissa12@gmail.com
// Created by alon on 5/20/24.
//

#ifndef CPP_EX3_24_MAIN_BOARD_H
#define CPP_EX3_24_MAIN_BOARD_H

#include <string>
#include "Resources.hpp" //todo: pay attention for loop include!

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
class DevelopmentCard;

class Settlement;

class City;

class Road;

class UrbanEntity;

class Player;

class DevelopmentCardsDeck;

namespace ariel {
    class Tile { //todo: add ports?
    private:
        bool isSea;
        bool isDesert;
        int number;
        std::string resource;
        Tile *neighbors[6];
        UrbanEntity *UrbanEntities[6];
        Road *roads[6];
    private:
        Settlement &removeSettlement(Settlement &settlement);

    public:
        Tile(int dieNum, std::string resource, bool issea = false, bool isDesert = false);

        void UpdateNeighbor(Tile &neighbor);

        void placeUrbanEntity(UrbanEntity &UrbanEntity);

        void placeRoad(Road &road);

    };

    class Board {
    private:
        Tile *tiles[37];
    public:
        Board();

        void printBoard();
    };

}
#endif //CPP_EX3_24_MAIN_BOARD_H
