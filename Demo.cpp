// 211344015 alonsuissa12@gmail.com
/**
 * Demo file for Ex3.
 *
 */
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Resources.hpp"

using namespace ariel;
using namespace std;

#define ROLL_DICE 1
#define PLACE_ROAD 2
#define PLACE_SETTLEMENT 3
#define PLACE_CITY 4
#define BUY_DEVELOPMENT_CARD 5
#define SEE_YOUR_DEVELOPMENT_CARD 6
#define USE_DEVELOPMENT_CARD 7
#define SEE_YOUR_RESOURCES 8 //todo: add this option to player
#define TRADE_WITH_PLAYERS 9
#define TRADE_WITH_THE_BANK 10
#define END_YOUR_TURN 11
//todo: add print board option

void printOptions();

Tile *chooseTile(Catan *gameManager);

int doAction(int action, Player *p);

void startGame(Catan *gm, int numOfPlayers);


int main() {
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3);


    // Starting of the game. Every player places two settlements and two roads.
    Player *p = catan.chooseStartingPlayer();   // should print the name of the starting player
    cout << "starting player: " << p->getName() << "\n";
    Board *board = catan.getBoard(); // get the board of the game.
    board->printBoard();

    board->printNeighbors();


    startGame(&catan, 3);


    bool gameOver = catan.isGameOver();


    while (!gameOver) {
        int playing = 1;
        int action = 0;

        while (playing) {
            cout << "\n" << p->getName() << ", what would you like to do on your turn?(type the number to choose)\n";
            printOptions();
            cin >> action;
            int playing = doAction(action, p);
        }

    }




//    p1.placeSettelemnut(places, placesNum);
//    p1.placeRoad(places, placesNum, board);
//    vector<string> places = {"Agricultural Land", "Desert"};
//    vector<int> placesNum = {3, 4};
//    p1.placeSettelemnt(places, placesNum, board);
//    p1.placeRoad(places, placesNum, board); // p1 chooses Forest, hills, Agricultural Land, Desert with numbers 5, 6, 3, 4.
//
//    vector<string> places = {"Mountains", "Pasture Land"};
//    vector<int> placesNum = {4, 9};
//    p2.placeSettelemnt(places, placesNum, board);
//    p2.placeRoad(places, placesNum, board);
//    try
//    {
//        p3.placeSettelemnt(places, placesNum, board); // p3 tries to place a settlement in the same location as p2.
//    }
//    catch (const std::exception &e)
//    {
//        cout << e.what() << endl;
//    }
//    vector<string> places = {"Forest", "Pasture Land"};
//    vector<int> placesNum = {5, 9};
//    p2.placeSettelemnt(places, placesNum, board);
//    p2.placeRoad(places, placesNum, board); // p2 chooses Mountains, Pasture Land, and Forest with numbers 4, 9, 5.
//
//    vector<string> places = {"Mountains", "Pasture Land"};
//    vector<int> placesNum = {3, 8};
//    p3.placeSettelemnt(places, placesNum, board);
//    p3.placeRoad(places, placesNum, board);
//    vector<string> places = {"Agricultural Land", "Pasture Land"};
//    vector<int> placesNum = {3, 9};
//    p3.placeSettelemnt(places, placesNum, board);
//    p3.placeRoad(places, placesNum, board); // p3 chooses Mountains, Pasture Land, Agricultural Land, Pasture Land with numbers 3, 8, 3, 9.
//
//    // p1 has wood,bricks, and wheat, p2 has wood, ore, and wool, p3 has ore, wool, wheat.
//    p1.rollDice();                                    // Lets say it's print 4. Then, p2 gets ore from the mountations.
//    p1.placeRoad({"Forest", "Hills"}, {5, 6}, board); // p1 continues to build a road.
//    p1.endTurn();                                     // p1 ends his turn.
//
//    p2.rollDice(); // Lets say it's print 9. Then, p3 gets wool from the Pasture Land, p2 gets wool from the Pasture Land.
//    p2.endTurn();  // p2 ends his turn.
//
//    p3.rollDice(); // Lets say it's print 3. Then, p3 gets wheat from the Agricultural Land and Ore from the Mountains, p1 gets wheat from the Agricultural Land.
//    p3.endTurn();  // p3 ends his turn.
//
//    try
//    {
//        p2.rollDice(); // p2 tries to roll the dice again, but it's not his turn.
//    }
//    catch (const std::exception &e)
//    {
//        cout << e.what() << endl;
//    }
//
//    p1.rollDice();                       // Lets say it's print 6. Then, p1 gets bricks from the hills.
//    p1.trade(p2, "wood", "brick", 1, 1); // p1 trades 1 wood for 1 brick with p2.
//    p1.endTurn();                        // p1 ends his turn.
//
//    p2.rollDice();           // Lets say it's print 9. Then, p3 gets wool from the Pasture Land, p2 gets wool from the Pasture Land.
//    p2.buyDevelopmentCard(); // p2 buys a development card. Lets say it is a bonus points card.
//    p2.endTurn();            // p2 ends his turn.
//
//    p1.printPoints(); // p1 has 2 points because it has two settelments.
//    p2.printPoints(); // p2 has 3 points because it has two settelments and a bonus points card.
//    p3.printPoints(); // p3 has 2 points because it has two settelments.
//
//    catan.printWinner(); // Should print None because no player reached 10 points.
}


void printOptions() {
    std::cout << "Options:" << std::endl;
    std::cout << "1. Roll the dice" << std::endl;
    std::cout << "2. Place a road" << std::endl;
    std::cout << "3. Place a settlement" << std::endl;
    std::cout << "4. Place a city" << std::endl;
    std::cout << "5. Buy a development card" << std::endl;
    std::cout << "6. See your development cards" << std::endl;
    std::cout << "7. Use a development card" << std::endl;
    std::cout << "8. See your resources" << std::endl;
    std::cout << "9. Trade with other players" << std::endl;
    std::cout << "10. Trade with the bank" << std::endl;
    std::cout << "11. End your turn" << std::endl;
}

// a function to ask for the player to choose a tile. the function will return a pointer to that tile
Tile *chooseTile(Catan *gameManager) {
    int resource = -1;
    int tileNumber = -1;
    bool validTile = false;
    Tile *t;
    std::cout << "----please choose a tile by choosing a resource and a number" << std::endl;
    while (!validTile) { // while the choice is invalid
        std::cout
                << "----Enter the resource of the tile (0 for brick, 1 for iron, 2 for wheat, 3 for wood, 4 for wool):\n";
        std::cin >> resource;

        std::cout << "----Enter the dice number of the tile:\n";
        std::cin >> tileNumber;
        t = gameManager->findTile(tileNumber, resource); // find this tile and return a pointer to it
        validTile = (resource >= 0 && resource <= 4) && (tileNumber >= 2 && tileNumber <= 12) && (t != nullptr);

        if (!validTile) {
            std::cout << "Invalid tile. Please try again.\n";
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }
    }
    return t;
}

// a function to resolve an action of a player on his turn
int doAction(int action, Player *p) {


    if (action == ROLL_DICE) {
        if (p->getRolledDice()) { // todo: pass rolled
            std::cout << "You can roll the dice only once per turn!." << std::endl;
            return 1;
        }
        std::cout << "You chose to roll the dice." << std::endl;
        p->rollDice();
    } else if (action == PLACE_ROAD) {
        std::cout << "You chose to place a road." << std::endl;
        std::cout << "chose two tiles to place between them." << std::endl;
        Tile *t1 = chooseTile(p->getGameManager());
        Tile *t2 = chooseTile(p->getGameManager());
        p->placeRoad(t1, t2);
    } else if (action == PLACE_SETTLEMENT) {
        std::cout << "You chose to place a settlement." << std::endl;
    } else if (action == PLACE_CITY) {
        std::cout << "You chose to place a city." << std::endl;

    } else if (action == BUY_DEVELOPMENT_CARD) {
        std::cout << "You chose to buy a development card." << std::endl;
    } else if (action == SEE_YOUR_DEVELOPMENT_CARD) {
        std::cout << "You chose to see your development cards." << std::endl;
    } else if (action == USE_DEVELOPMENT_CARD) {
        std::cout << "You chose to use a development card." << std::endl;
    } else if (action == SEE_YOUR_RESOURCES) {
        std::cout << "You chose to see your resources." << std::endl;
    } else if (action == TRADE_WITH_PLAYERS) {
        std::cout << "You chose to trade with other players." << std::endl;
    } else if (action == TRADE_WITH_THE_BANK) {
        std::cout << "You chose to trade with the bank." << std::endl;
    } else if (action == END_YOUR_TURN) {
        std::cout << "You chose to end your turn." << std::endl;
    } else {
        std::cout << "Invalid choice. Please choose a number between 1 and 11." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return 0;
}

// a function to place the starting set up of the board presents of the players
void startGame(Catan *gm, int numOfPlayers) {
    for (int i = 0; i < numOfPlayers * 2; ++i) { // twice for each player place a settlement and a road
        Player *p = gm->getPlayerTurn();

        //place a settlement
        int placed =-1;
        while (placed== -1) {
            cout << p->getName() << " for placing a settlement please chose 3 tiles (to place between them)\n ";
            Tile *t1 = chooseTile(gm);
            Tile *t2 = chooseTile(gm);
            Tile *t3 = chooseTile(gm);
            placed = p->placeSettlement(t1, t2, t3, true);
            if(placed == -1)
                cout << "please try again\n";
        }
        placed = -1;
        //place a road
        while (placed== -1) {
            cout << p->getName() << " for placing a road please chose 2 tiles (to place between them)\n ";
            cout << p->getName() << " pay attention that the road have to be continues to your board present\n";
            Tile *t1 = chooseTile(gm);
            Tile *t2 = chooseTile(gm);
            placed = p->placeRoad(t1, t2);
            if(placed == -1)
                cout << "please try again\n";
        }

        p->endTurn();
    }
}