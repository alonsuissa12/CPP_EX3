// 211344015 alonsuissa12@gmail.com
// Created by alon on 5/20/24.
//

#ifndef CPP_EX3_24_MAIN_RESOURCES_H
#define CPP_EX3_24_MAIN_RESOURCES_H

#include <string>
#include <vector>
#include <stdexcept>
#include <random>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <functional>


#define BRICK 0
#define IRON 1
#define WHEAT 2
#define WOOD 3
#define WOOL 4
#define DESERT 5
#define SEA 6

#define DEBUG(x) std::cout << x << std::endl;


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
    int edgeSide(Tile &, Tile &);

    class Road {
    private:
        Player *owner;
        Tile *neighborTile1;
        Tile *neighborTile2;

    public:
        Road(Player *owner);

        int place(Tile &n1, Tile &n2);

        std::string getOwnerName();

        Player *getOwner();

    };

    class UrbanEntity {
    protected:
        int type;
        ariel::Player *owner;
        int numOfResources;
        int numOfVictoryPoints;
        Tile *neighborTileRight;
        Tile *neighborTileLeft;
        Tile *neighborTileDown;


        friend class Catan;

    public:
        virtual ~UrbanEntity();

        Player *getOwner();

        std::string getOwnerName();

        int getNumOfResources();

        int getNumOfVictoryPoints();

        Tile *getNeighbor(int num);

        int getType();

        virtual int place(Tile &n1, Tile &n2, Tile &n3, bool start = false) = 0;


    };

    class Settlement : public UrbanEntity {
    public:
        explicit Settlement(Player *);

        int place(Tile &n1, Tile &n2, Tile &n3, bool start) override;
    };

    class City : public UrbanEntity {
    public:
        explicit City(Player *);

        int place(Tile &n1, Tile &n2, Tile &n3, bool start) override;
    };

    class DevelopmentCard {
    protected:
        std::string name;
        Catan *gameManager;
    public:
        virtual void playCard(Player &p) = 0;

        virtual ~DevelopmentCard();

        std::string getName();

    };

    class VictoryPoint : public DevelopmentCard {
    public:
        VictoryPoint(Catan *);

        void playCard(Player &p) override;
    };

    class Knight : public DevelopmentCard {
    public:
        Knight(Catan *);

        void playCard(Player &p) override;
    };

    class Monopole : public DevelopmentCard {
    public:
        Monopole(Catan *);

        void playCard(Player &p) override;
    };

    class RoadsBuild : public DevelopmentCard {
    public:
        RoadsBuild(Catan *);

        void playCard(Player &p) override;
    };

    class YearOfPlenty : public DevelopmentCard {
    public:
        YearOfPlenty(Catan *);

        void playCard(Player &p) override;
    };


    class Tile {
    private:
        bool isSea;
        bool isDesert;
        int number;
        std::string resource;
        Tile *neighbors[6];
        UrbanEntity *urbanEntities[6];
        Road *roads[6];

        friend class Catan;

        friend class Board;

    private:
        Settlement &removeSettlement(Settlement &settlement);

    public:
        Tile(int dieNum, std::string resource, bool issea, bool isDesert);

        void UpdateNeighbor(Tile &neighbor, int side);

        int placeUrbanEntity(UrbanEntity *UrbanEntity, int side);

        int placeRoad(Road *road, int side);

        Tile *getNeighbor(int side);

        Road *getRoad(int side);

        UrbanEntity *getUrbanEntity(int side);

        int getResource();

        int getNumber();

        bool getIsSea();

        bool getIsDesert();

        friend std::ostream &operator<<(std::ostream &os, const Tile &tile);


    };

    class Board {
    private:
        std::vector<Tile *> tiles;
    public:
        Board();

        ~Board();

        void printBoard();

        Tile *findTile(int numTile, int resourceTile);

        void printNeighbors();

    };

    class Catan {
    private:
        Board *board;
        std::vector<Player *> players;
        unsigned int playerTurn;
        bool gameOver;


    private:
        void monopole(Player *p, int resource);

        int myChooseStartingPlayer();

    public:
        Catan(Player &p1, Player &p2, Player &p3);

        ~Catan();

        Board *getBoard();

        void printWinner();

        Player *chooseStartingPlayer();

        // updates the players resourced according to the dice roll
        void diceRoll(int);

        Tile *findTile(int numTile, int resourceTile);

        Player *getPlayerTurn();

        void nextTurn();

        DevelopmentCard *buyDevelopmentCard();


        void win(Player &p);

        bool isGameOver();

        void addResourcesTO(Player *p, Tile *t);

        void printPlayers();

        Player *getPlayer(int x);


        friend class Monopole;

        friend class RoadsBuild;

        friend class YearOfPlenty;
    };

    bool operator==(const Tile &t1, const Tile &t2);

    bool operator!=(const Tile &t1, const Tile &t2);


    class Player {

    private:
        static int playerNum;
        std::string name;
        Catan *gameManager;
        int VictoryPoints;
        int numOfKnights;
        bool playedDevelopmentCard;
        bool rolledDiceThisTurn;
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

        friend class Tile;

    private:
        void takeBackSettlement(Settlement *ps);

    public:
        // This function constructs a Player object with default attributes and initializes resources and urban entities.
        // It assigns a default name and increments the player number.
        Player();

        // This function constructs a Player object with a specified name and initializes resources and urban entities.
        // It increments the player number.

        explicit Player(std::string name);

        // Destructor for the Player class.
        // It deallocates all settlements, cities, roads, and development cards.
        ~Player();

        // Assigns the Catan game manager to the player.

        void joinGame(Catan *gm);

        // Simulates rolling two dice and returns their sum.
        // It also updates the game manager with the dice roll result, which will resolve the result for all players.
        int rollDice();

        // Places a road between two specified tiles on the board.
        int placeRoad(int numTile1, int resourceTile1, int numTile2, int resourceTile2);

        // Places a road between two specified tiles on the board.
        int placeRoad(int numTile1, std::string resourceTile1, int numTile2, std::string resourceTile2);

        // Places a road between two specified tiles on the board.
        int placeRoad(Tile *t1, Tile *t2);

        // Places a settlement at the intersection of three specified tiles on the board.
        int placeSettlement(int numTile1, std::string resourceTile1, int numTile2, std::string resourceTile2,
                            int numTile3, std::string resourceTile3, bool start);

        // Places a settlement at the intersection of three specified tiles on the board.
        int placeSettlement(Tile *t1, Tile *t2, Tile *t3, bool start);

        // Places a settlement at the intersection of three specified tiles on the board.
        int placeSettlement(int numTile1, int resourceTile1, int numTile2, int resourceTile2, int numTile3,
                            int resourceTile3, bool start);

        // Places a city at the intersection of three specified tiles on the board.
        int placeCity(int numTile1, std::string resourceTile1, int numTile2, std::string resourceTile2, int numTile3,
                      std::string resourceTile3, bool start);

        // Places a city at the intersection of three specified tiles on the board.
        int placeCity(int numTile1, int resourceTile1, int numTile2, int resourceTile2, int numTile3, int resourceTile3,
                      bool start);

        // Places a city at the intersection of three specified tiles on the board.
        int placeCity(Tile *t1, Tile *t2, Tile *t3, bool start);

        // Buys a development card from the game manager.
        int buyDevelopmentCard();

        // Retrieves the development cards owned by the player and prints them.
        std::vector<DevelopmentCard *> getDevelopmentCards();

        // Uses a development card.
        int useDevelopmentCard(DevelopmentCard *dc);

        // Initiates a trade with another player.
        int trade(Player *other, int wantedResource, int wantedAmount, int givenResource, int givenAmount);

        // Trade with the bank 4 resources for one resource
        int tradeWithTheBank(int wantedResource, int givenResource);

        // Retrieves the player's victory points.
        int getVictoryPoints();

        // Retrieves the player's name.
        std::string getName();

        // Retrieves whether the player has rolled the dice during their turn.
        bool getRolledDice();

        // Ends the player's turn by resetting the played development card flag and checking for victory conditions.
        void endTurn();

        // Retrieves the game manager associated with the player.
        Catan *getGameManager();

        // Prints the resources owned by the player.
        void printResources();

    };


    // Converts a resource name string to its corresponding integer representation.
    int convertResourceToInt(std::string resourceTile1);

    // Converts an integer representation of a resource to its corresponding string representation.
    std::string convertResourceToString(int resource);

    // Overloaded equality operator for comparing two Player objects.
    bool operator==(const Player &p1, const Player &p2);

    // Overloaded inequality operator for comparing two Player objects.
    bool operator!=(const Player &p1, const Player &p2);


}

#endif //CPP_EX3_24_MAIN_RESOURCES_H
