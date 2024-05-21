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
#include "Board.hpp"
#include <string>
#include <vector>



namespace ariel {
    class DevelopmentCard;

    class Settlement;

    class City;

    class Road;

    class UrbanEntity;

    class Tile;

    class DevelopmentCardsDeck;


    class Player { //todo: operator overloading to == and !=

    private:
        std::string name;
        int VictoryPoints;
        int numOfKnights;
        std::vector <DevelopmentCard*> developmentCards;
        std::vector <Settlement*> unusedSettlements;
        std::vector <City*> unusedCities;
        std::vector <Road*> unusedRoads;
        std::vector <UrbanEntity*> usedUrbanEntities;
        std::vector <Road*> usedRoads;
        int resources[5];

        friend class DevelopmentCard;
        friend class VictoryPoint;
        friend class Knight;
        friend class Monopole;
        friend class RoadsBuild;
        friend class YearOfPlenty;



    public:
        Player();

        Player(std::string name);

        int rollDice();

        void placeRoad(int numTile1, std::string resourceTile1, int numTile2, std::string resourceTile2);

        void placeRoad(Tile &t1, Tile t2);

        void
        placeSettlement(int numTile1, std::string resourceTile1, int numTile2, std::string resourceTile2, int numTile3,
                        std::string resourceTile3);

        void placeSettlement(Tile &t1, Tile t2, Tile t3);

        void placeCity(int numTile1, std::string resourceTile1, int numTile2, std::string resourceTile2, int numTile3,
                       std::string resourceTile3);

        void placeCity(Tile &t1, Tile t2, Tile t3);

        void buyDevelopmentCard(DevelopmentCardsDeck);

        std::vector <DevelopmentCard> getDevelopmentCards();

        void useDevelopmentCard(DevelopmentCard *dc);

        void trade(Player other, int wantedResource, int wantedAmount, int givenResource, int givenAmount);

        void tradeWithTheBank(int wantedResource, int wantedAmount);

        void takeResources(int brick, int iron, int wheat, int wood, int wool);

        void useResources(int brick, int iron, int wheat, int wood, int wool);

        int getVictoryPoints();

        std::string getName();



        void endTurn();

    };

}
#endif //CPP_EX3_24_MAIN_PLAYER_H
