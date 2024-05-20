//
// Created by alon on 5/20/24.
//

#ifndef CPP_EX3_24_MAIN_PLAYER_H
#define CPP_EX3_24_MAIN_PLAYER_H

#include "Resources.h"
#include "Board.h"
#include <string.h>

#ifndef BRICK
#define BRICK 0
#define IRON 1
#define WHEAT 2
#define WOOL 3
#define WOOD 4
#endif


class Player {
private:
    std::string name;
    int VictoryPoints;
    std::vector <DevelopmentCard> developmentCards;
    std::vector <Settlement> unusedSettlements;
    std::vector <City> unusedCities;
    std::vector <Road> unusedRoads;
    std::vector <UrbanEntity> usedUrbanEntities;
    std::vector <Road> usedRoads;
    int [] resources;

public:
    Player(std::string name);
    int rollDice();
    void placeRoad(numTile1, resourceTile1, numTile2, resourceTile2);
    void placeRoad(Tile & t1, Tile t2);
    void placeSettlement(numTile1, resourceTile1, numTile2, resourceTile2, numTile3, resourceTile3);
    void placeSettlement(Tile & t1, Tile t2, Tile t3);
    void placeCity(numTile1, resourceTile1, numTile2, resourceTile2, numTile3, resourceTile3);
    void placeCity(Tile & t1, Tile t2, Tile t3);
    void buyDevelopmentCard();
    std::vector<DevelopmentCard> getDevelopmentCards();
    void useDevelopmentCard(DevelopmentCard dc);
    void trade(Player other, int wantedResource, int wantedAmount, int givenResource, int givenAmount);
    void endTurn();

};


#endif //CPP_EX3_24_MAIN_PLAYER_H
