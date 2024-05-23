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
#include <random>
#include <ctime>
#include <algorithm>
#include <iostream>

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
    class Catan;

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
        Player * owner;
        Tile *neighborTile1;
        Tile *neighborTile2;

    public:
        Road(Player *owner);

        int place( Tile &n1, Tile &n2);

        std::string getOwnerName();

        Player * getOwner();

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

        friend class Catan;
    public:
        Player *getOwner();

        std::string getOwnerName();

        int getNumOfResources();

        int getNumOfVictoryPoints() ;

        Tile *getNeighbor(int num);

        int getType();

        virtual int place(Tile &n1, Tile &n2, Tile &n3,bool start = false) = 0;



    };

    class Settlement : public UrbanEntity {
    public:
        explicit Settlement(Player *);
        int place(Tile &n1, Tile &n2, Tile &n3, bool start) override;
    };

    class City : public UrbanEntity {
    public:
        explicit City(ariel::Player *);
        int place(Tile &n1, Tile &n2, Tile &n3, bool start ) override;
    };

    class DevelopmentCard {
    protected:
        std::string name;
        Catan* gameManager;
    public:
        virtual void playCard(Player &p) = 0;
        std::string getName();

    };

    class VictoryPoint : public DevelopmentCard {
    public:
        VictoryPoint(Catan*);

        void playCard(Player &p) override;
    };

    class Knight : public DevelopmentCard {
    public:
        Knight(Catan*);

        void playCard(Player &p) override;
    };

    class Monopole : public DevelopmentCard {
    public:
        Monopole(Catan*);

        void playCard(Player &p) override;
    };

    class RoadsBuild : public DevelopmentCard {
    public:
        RoadsBuild(Catan*);

        void playCard(Player &p) override;
    };

    class YearOfPlenty : public DevelopmentCard {
    public:
        YearOfPlenty(Catan*);

        void playCard(Player &p) override;
    };


//    class DevelopmentCardsDeck { //todo: delete
//    private:
//        std::vector <DevelopmentCard> deck;
//
//        void shuffle(std::vector <DevelopmentCard>);
//
//    public:
//        DevelopmentCardsDeck(); //
//        DevelopmentCard *draw();
//
//    };

    class Tile { //todo: add ports?
    private:
        bool isSea;
        bool isDesert;
        int number;
        std::string resource;
        Tile *neighbors[6];
        UrbanEntity *urbanEntities[6];
        Road * roads[6];

        friend class Catan;
    private:
        Settlement &removeSettlement(Settlement &settlement);

    public:
        Tile(int dieNum, std::string resource, bool issea, bool isDesert);

        void UpdateNeighbor(Tile &neighbor,int side);

        int placeUrbanEntity(UrbanEntity *UrbanEntity,int side);

        int placeRoad(Road *road, int side);

        Tile& getNeighbor(int side);

        Road * getRoad(int side);

        UrbanEntity * getUrbanEntity(int side);

        int getResource(); //todo: implement! (return the resource number!)

        int getNumber();



    };

    class Board { //todo: add destructor
    private:
        std::vector<Tile *>tiles;
    public:
        Board();

        void printBoard();
        Tile * findTile(int numTile, int resourceTile);

    };

    class Board;

    class Catan {
    private:
        Board *board;
        std::vector <Player*> players;
        unsigned int playerTurn;


    private:
        void monopole(Player *p, int resource);

        int myChooseStartingPlayer();
    public:
        Catan(Player &p1, Player &p2, Player &p3);

        Board* getBoard();

        void printWinner();

        Player* chooseStartingPlayer();

        // updates the players resourced according to the dice roll
        void diceRoll(int);

        Tile * findTile(int numTile, int resourceTile);

        Player *getPlayerTurn();

        void nextTurn();

        DevelopmentCard * buyDevelopmentCard(); // todo: implement


        void win(Player& p); // todo: implement


        friend class Monopole;
        friend class RoadsBuild;
        friend class YearOfPlenty;
    };

    bool operator==(const Tile& t1, const Tile & t2);
    bool operator!=(const Tile& t1, const Tile & t2);

}

#endif //CPP_EX3_24_MAIN_RESOURCES_H
