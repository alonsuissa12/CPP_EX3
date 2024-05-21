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

#define RightTile 0
#define LeftTile 1
#define DownTile 2



#define SETTLEMENT 1
#define CITY 2

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

    //find the edge side from n1 to n2
    int edgeSide(Tile&,Tile&);

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
    protected:
        int type;
        ariel::Player * owner;
        int numOfResources;
        int numOfVictoryPoints;
        Tile *neighborTileRight;
        Tile *neighborTileLeft;
        Tile *neighborTileDown;
    public:
        Player *getOwner();

        std::string getOwnerName();

        int getNumOfResources();

        int getNumOfVictoryPoints() ;

        Tile *getNeighbor(int num);

        int getType();

        virtual void place(Tile &n1, Tile &n2, Tile &n3,bool start = false) = 0;



    };

    class Settlement : public UrbanEntity {
    public:
        explicit Settlement(Player *);
        void place(Tile &n1, Tile &n2, Tile &n3, bool start) override;
    };

    class City : public UrbanEntity {
    public:
        explicit City(ariel::Player *);
        void place(Tile &n1, Tile &n2, Tile &n3, bool start ) override;
    };

    class DevelopmentCard {
    protected:
        std::string name;
    public:
        virtual void playCard(Player &p) = 0;

    };

    class VictoryPoint : public DevelopmentCard {
    public:
        VictoryPoint();

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

        void placeUrbanEntity(UrbanEntity *UrbanEntity,int side);

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
