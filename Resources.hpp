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
// todo: make it 2
#define StartingPlacing 1

namespace ariel {
    class Catan;

    class DevelopmentCard;

    class Settlement;

    class City;

    class UrbanEntity;

    class Player;


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
        // Constructor for Road class
        explicit Road(Player *owner);

        // Function to place the road between two tiles
        int place(Tile &n1, Tile &n2);

        // Function to get the owner's name of the road
        std::string getOwnerName();

        // Function to get the owner of the road
        Player *getOwner();

        Tile *getNeighbor(int side);

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
        // Destructor for UrbanEntity
        virtual ~UrbanEntity();

        // Getter for the owner of the UrbanEntity
        Player *getOwner();

        // Getter for the name of the owner of the UrbanEntity
        std::string getOwnerName();

        // Getter for the number of resources this urban entity generates
        int getNumOfResources();

        // Getter for the number of victory points this urban entity is worth
        int getNumOfVictoryPoints();

        // Getter for the neighboring Tile of this urban entity
        Tile *getNeighbor(int num);

        // Getter for the type of the urban entity
        int getType();

        virtual int place(Tile &n1, Tile &n2, Tile &n3, bool start = false) = 0;


    };

    class Settlement : public UrbanEntity {
    public:
        // Constructor for Settlement
        explicit Settlement(Player *);

        // Function to place a Settlement on the board
        int place(Tile &n1, Tile &n2, Tile &n3, bool start) override;
    };

    class City : public UrbanEntity {
    public:
        // Constructor for City
        explicit City(Player *);

        // Function to place a City on the board
        int place(Tile &n1, Tile &n2, Tile &n3, bool start) override;
    };

    class DevelopmentCard {
    protected:
        std::string name;
        Catan *gameManager;
    public:
        virtual void playCard(Player &p) = 0;

        virtual ~DevelopmentCard();

        // returns the name of the card
        std::string getName();

    };

    class VictoryPoint : public DevelopmentCard {
    public:
        // a constructor for victor point development card
        explicit VictoryPoint(Catan *);

        // activate the card's effect - add 1 VP to the player
        void playCard(Player &p) override;
    };

    class Knight : public DevelopmentCard {
    public:
        // a constructor for knight point development card
        explicit Knight(Catan *);

        // activate the card's effect - add 1 Knight to the player (the players with most knights gets 2 VP)
        void playCard(Player &p) override;
    };

    class Monopole : public DevelopmentCard {
    public:
        // a constructor for monopoly development card
        explicit Monopole(Catan *);

        // activate the card's effect - takes from all the other players
        // all the resources of one type and gives it to the activating player
        void playCard(Player &p) override;
    };

    class RoadsBuild : public DevelopmentCard {
    public:
        // a constructor for roads build development card
        explicit RoadsBuild(Catan *);

        // activate the card's effect - lets the activating player place 2 roads
        void playCard(Player &p) override;
    };

    class YearOfPlenty : public DevelopmentCard {
    public:
        // a constructor for year of plenty development card
        explicit YearOfPlenty(Catan *);

        // activate the card's effect - lets the activating player get 2 resources of his choice
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

    public:
        // Constructor for the Tile class.
        Tile(int dieNum, std::string resource, bool issea, bool isDesert);

        // Updates the neighbor of the current tile on a specific side.
        void UpdateNeighbor(Tile &neighbor, int side);

        // Places an urban entity (Settlement or City) on the specified side of the tile.
        int placeUrbanEntity(UrbanEntity *UrbanEntity, int side);

        // Places a road on the specified side of the tile.
        int placeRoad(Road *road, int side);

        // Retrieves the neighbor of the current tile on a specific side.
        Tile *getNeighbor(int side);

        // Retrieves the road on the specified side of the tile.
        Road *getRoad(int side);

        // Retrieves the urban entity (Settlement or City) on the specified side of the tile.
        UrbanEntity *getUrbanEntity(int side);

        // Retrieves the resource type of the tile.
        int getResource();

        // Retrieves the number associated with the tile.
        int getNumber();

        // Retrieves whether the tile is a sea tile.
        bool getIsSea();

        // Retrieves whether the tile is a desert tile.
        bool getIsDesert();

        // Overloaded stream insertion operator to print a tile.
        friend std::ostream &operator<<(std::ostream &os, const Tile &tile);


    };

    // Overloaded equality operator for comparing two tiles.
    bool operator==(const Tile &t1, const Tile &t2);

    // Overloaded inequality operator for comparing two tiles.
    bool operator!=(const Tile &t1, const Tile &t2);

    class Board { // todo add non-random board
    private:
        std::vector<Tile *> tiles;
    public:
        // Constructor for the Board class.
        explicit Board(bool constant);

        // Destructor for the Board class.
        ~Board();

        // Prints the Catan game board with tiles arranged in a hexagonal pattern.
        void printBoard();

        // Finds a tile with a specific number and resource type.
        Tile *findTile(int numTile, int resourceTile);

        // Prints the neighbors of each tile on the board.
        void printNeighbors();

    };

    class Catan {
    private:
        Board *board;
        std::vector<Player *> players;
        unsigned int playerTurn;
        bool gameOver;


    private:
        // Implements the "Monopoly" action
        void monopole(Player *p, int resource);

        // Helper function to randomly select the starting player index
        int myChooseStartingPlayer();

    public:
        // Constructor for the Catan game class
        Catan(Player &p1, Player &p2, Player &p3, bool contBoard);

        // Destructor for the Catan game class
        ~Catan();

        // Returns a pointer to the game board
        Board *getBoard();

        // Prints the name of the player who has won
        void printWinner();

        // Returns a pointer to the current starting player
        Player *chooseStartingPlayer();

        // updates the players resourced according to the dice roll
        void diceRoll(int);

        // Finds a tile on the game board by number and resource type
        Tile *findTile(int numTile, int resourceTile);

        // Returns the player whose turn it is
        Player *getPlayerTurn();

        // Moves to the next turn in the game
        void nextTurn();

        // Allows a player to buy a random development card
        DevelopmentCard *buyDevelopmentCard();

        // Declares a winner and updates that the game is over
        void win(Player &p);

        // Returns true if the game is over
        bool isGameOver();

        // Adds resources to a player based on a tile
        void addResourcesTO(Player *p, Tile *t);

        // Prints the names of all players in the game
        void printPlayers();

        // Returns the player at the specified index
        Player *getPlayer(int x);

        void printBoardPresent();


        friend class Monopole;

        friend class RoadsBuild;

        friend class YearOfPlenty;
    };


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
        int trade(Player *other, int wantedResource, int wantedAmount, int givenResource, int givenAmount,
                  bool askForAccept = true);

        // trade a development card of yours with another player's development card
        int tradeDevelopmentCardForDevelopmentCard(std::string wantedDC, Player *other, std::string givedDC,
                                                   bool askForAccept);

        // Trade with the bank 4 resources for one resource
        int tradeWithTheBank(int wantedResource, int givenResource);

        // Retrieves the player's victory points.
        int getVictoryPoints();

        // Retrieves the player's number of knights.
        int getNumOfKnights();

        // Retrieves the player's name.
        std::string getName();

        // Retrieves whether the player has rolled the dice during their turn.
        bool getRolledDice();

        // Ends the player's turn by resetting the played development card flag and checking for victory conditions.
        void endTurn();

        // Retrieves the game manager associated with the player.
        Catan *getGameManager();

        const int *getResources() const;

        // Prints the resources owned by the player.
        void printResources();

        // print your board presents
        void printBoardPresent();

        bool canPlaceSettlement() {
            return resources[BRICK] > 0 && resources[WHEAT] > 0 && resources[WOOD] > 0 && resources[WOOL] > 0;
        }

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
