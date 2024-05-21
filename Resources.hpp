// 211344015 alonsuissa12@gmail.com
// Created by alon on 5/20/24.
//

#ifndef CPP_EX3_24_MAIN_RESOURCES_H
#define CPP_EX3_24_MAIN_RESOURCES_H

//#include "Board.hpp" //todo: pay attention for loop include!
#include "Player.hpp"
#include <string>
#include <vector>
#include <stdexcept>

#define RightEdge 0
#define UpRightEdge 1
#define UpLeftEdge 2
#define LeftEdge 3
#define DownLeftEdge 4
#define DownRightEdge 5

#define DownRightVertex 0
#define UpRightVertex 1
#define UpVertex 2
#define UpLeftVertex 3
#define DownLeftVertex 4
#define DownVertex 5



#define SETTLEMENT 2
#define CITY 1

namespace ariel {

    class DevelopmentCard;

    class Settlement;

    class City;

    class Road;

    class UrbanEntity;

    class Player;

    class DevelopmentCardsDeck;
    class Tile;
    class Board;

    class Road {
    private:
        std::string ownerName;
        Tile *neighborTile1;
        Tile *neighborTile2;

    public:
        Road(std::string owner);

        void place( Tile &n1, Tile &n2);

        std::string getOwnerName();

    };

    class UrbanEntity {
    public:
        virtual std::string getOwner() = 0;

        virtual int getNumOfResources() = 0;

        virtual int getNumOfVictoryPoints() = 0;

        virtual Tile &getNeighbor(int num) = 0;

        virtual void place(Tile &n1, Tile &n2, Tile &n3) = 0;

        virtual int getType() = 0;

    };

    class Settlement : public UrbanEntity {
    private:
        int type;
        std::string ownerName;
        int numOfResources;
        int numOfVictoryPoints;
        Tile &neighborTile1;
        Tile &neighborTile2;
        Tile &neighborTile3;
    public:
        Settlement(std::string owner);
        Tile & getNeighbor(int num) override;
        std::string getOwner() override;
        int getNumOfResources() override;
        int getNumOfVictoryPoints() override;
        int getType() override;
        void place(Tile &n1, Tile &n2, Tile &n3) override;
    };

    class City : public UrbanEntity {
    private:
        int type;
        std::string ownerName;
        int numOfResources;
        int numOfVictoryPoints;
        Tile &neighborTile1;
        Tile &neighborTile2;
        Tile &neighborTile3;
    public:
        City(std::string);
        Tile & getNeighbor(int num) override;
        std::string getOwner() override;
        int getNumOfResources() override;
        int getNumOfVictoryPoints() override;
        int getType() override;
        void place(Tile &n1, Tile &n2, Tile &n3) override;

    };

    class DevelopmentCard { //todo: make it interface and create inheriting types
    protected:
        std::string name;
    public:
        virtual void playCard(Player &p) = 0;
    };

    class VictoryPoint : public DevelopmentCard {
    public:
        VictoryPoint(std::string name);

        void playCard(Player &p) override;
    };

    class Knight : public DevelopmentCard {
    public:
        Knight();

        void playCard(Player &p) override;
    };

    class Monopole : public DevelopmentCard {
    public:
        Monopole();

        void playCard(Player &p) override;
    };

    class RoadsBuild : public DevelopmentCard {
    public:
        RoadsBuild();

        void playCard(Player &p) override;
    };

    class YearOfPlenty : public DevelopmentCard {
    public:
        YearOfPlenty();

        void playCard(Player &p) override;
    };


    class DevelopmentCardsDeck {
    private:
        std::vector <DevelopmentCard> deck;

        void shuffle(std::vector <DevelopmentCard>);

    public:
        DevelopmentCardsDeck(); // todo: crate a deck with all the cards and shuffle it
        DevelopmentCard *draw();

    };

    class Tile { //todo: add ports?
    private:
        bool isSea;
        bool isDesert;
        int number;
        std::string resource;
        Tile *neighbors[6];
        UrbanEntity *UrbanEntities[6];
        Road * roads[6];
    private:
        Settlement &removeSettlement(Settlement &settlement);

    public:
        Tile(int dieNum, std::string resource, bool issea = false, bool isDesert = false);

        void UpdateNeighbor(Tile &neighbor);

        void placeUrbanEntity(UrbanEntity &UrbanEntity);

        void placeRoad(Road *road, int side);

        Tile& getNeighbor(int side);

        ariel::Road * getRoad(int side);

        UrbanEntity * getUrbanEntity(int side);

        bool equalTo(Tile other );



    };

    class Board {
    private:
        Tile *tiles[37];
    public:
        Board();

        void printBoard();
    };

}

#endif //CPP_EX3_24_MAIN_RESOURCES_H
