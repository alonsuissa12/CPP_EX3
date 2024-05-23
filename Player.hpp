// 211344015 alonsuissa12@gmail.com
// Created by alon on 5/20/24.
//

#ifndef CPP_EX3_24_MAIN_PLAYER_H
#define CPP_EX3_24_MAIN_PLAYER_H

#ifndef BRICK
#define BRICK 0
#define IRON 1
#define WHEAT 2
#define WOOD 3
#define WOOL 4
#endif

#include "Resources.hpp"
#include <string>
#include <vector>


namespace ariel {
    class Catan;

    class DevelopmentCard;

    class Settlement;

    class City;

    class Road;

    class UrbanEntity;

    class Tile;

    class DevelopmentCardsDeck;


    class Player {

    private:
        static int playerNum;
        std::string name;
        Catan *gameManager;
        int VictoryPoints;
        int numOfKnights;
        bool playedDevelopmentCard;
        std::vector<DevelopmentCard *> developmentCards;
        std::vector<Settlement *> unusedSettlements;
        std::vector<City *> unusedCities;
        std::vector<Road *> unusedRoads;
        std::vector<UrbanEntity *> usedUrbanEntities;
        std::vector<Road *> usedRoads;
        int resources[5];

        friend class DevelopmentCard;

        friend class VictoryPoint;

        friend class Knight;

        friend class Monopole;

        friend class RoadsBuild;

        friend class YearOfPlenty;

        friend class Catan;

    public:
        Player(Catan *gm);

        Player(Catan *gm, std::string name);

        int rollDice();

        int placeRoad(int numTile1, int resourceTile1, int numTile2, int resourceTile2);

        int placeRoad(int numTile1, std::string resourceTile1, int numTile2, std::string resourceTile2);

        int placeRoad(Tile *t1, Tile *t2);


        int placeSettlement(int numTile1, std::string resourceTile1, int numTile2, std::string resourceTile2, int numTile3,
                        std::string resourceTile3,bool start);

        int placeSettlement(Tile *t1, Tile *t2, Tile *t3,bool start);

        int placeSettlement(int numTile1, int resourceTile1, int numTile2, int resourceTile2,int numTile3, int resourceTile3,bool start);

        int placeCity(int numTile1, std::string resourceTile1, int numTile2, std::string resourceTile2, int numTile3,
                       std::string resourceTile3,bool start);
        int placeCity(int numTile1, int resourceTile1, int numTile2, int resourceTile2,int numTile3, int resourceTile3,bool start);

        int placeCity(Tile *t1, Tile* t2, Tile* t3,bool start);

        int buyDevelopmentCard();

        std::vector <DevelopmentCard*> getDevelopmentCards();

        int useDevelopmentCard(DevelopmentCard *dc);

        int trade(Player other, int wantedResource, int wantedAmount, int givenResource, int givenAmount);

        int tradeWithTheBank(int wantedResource, int wantedAmount);

        int takeResources(int brick, int iron, int wheat, int wood, int wool);

        int useResources(int brick, int iron, int wheat, int wood, int wool);

        int getVictoryPoints();

        std::string getName();

        void endTurn();

    };

    int Player::playerNum = 0;
    // converting the resource name to the resource int.
    int convertResourceToInt(std::string resourceTile1);

    bool operator==(const Player &p1, const Player &p2);

    bool operator!=(const Player &p1, const Player &p2);

}
#endif //CPP_EX3_24_MAIN_PLAYER_H
