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
#define SEE_YOUR_RESOURCES 8
#define TRADE_WITH_PLAYERS 9
#define TRADE_WITH_THE_BANK 10
#define TRADE_DEVELOPMENT_CARDS 11
#define END_YOUR_TURN 12
#define PRINT_BOARD 13//
#define SEE_YOUR_BOARD_PRESENT 14
#define SEE_EVERYONE_BOARD_PRESENT 15


#define NEXT_TURN 2
#define GAME_OVER 3


void printOptions();

Tile *chooseTile(Catan *gameManager);

int doAction(int action, Player *p);

void startGame(Catan *gm, int numOfPlayers);

// quick setup on fixed board:
//1,1,1,2,2,2
int main() {
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3, false);


    // Starting of the game. Every player places two settlements and two roads.
    Player *p = catan.chooseStartingPlayer();   // should print the name of the starting player
    cout << "starting player: " << p->getName() << "\n";
    Board *board = catan.getBoard(); // get the board of the game.
    board->printBoard();

//    board->printNeighbors();

    startGame(&catan, 3);
    bool gameOver = catan.isGameOver();

    while (!gameOver) {
        int action = 0;


        cout << "\n" << p->getName() << ", what would you like to do on your turn?(type the number to choose)\n";
        printOptions();
        cin >> action;
        int result = doAction(action, p);
        if (result == GAME_OVER)
            gameOver = true;
        else if (result == NEXT_TURN)
            p = catan.getPlayerTurn();
    }
    cout << "---------------------------------------------------------------------------------------------\n";
    cout << "======================================    GAME OVER    ======================================\n";
    cout << "---------------------------------------------------------------------------------------------\n";


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
    std::cout << "11. Trade development card" << std::endl;
    std::cout << "12. End your turn" << std::endl;
    std::cout << "13. print the board" << std::endl;
    std::cout << "14. see your board present" << std::endl;
    std::cout << "15. see everyone's board present" << std::endl;
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
                << "----Enter the resource of the tile (0 - brick, 1-iron, 2- wheat, 3-wood, 4-wool,5-desert,6-sea):\n";
        std::cin >> resource;

        std::cout << "----Enter the dice number of the tile: (5 for desert, index of sea for sea)\n";
        std::cin >> tileNumber;
        t = gameManager->findTile(tileNumber, resource); // find this tile and return a pointer to it
        validTile = (resource >= 0 && resource <= 6) && (tileNumber >= 0 && tileNumber <= 17) && (t != nullptr);

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
        if (p->getRolledDice()) {
            std::cout << "You can roll the dice only once per turn!." << std::endl;
            return 0;
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
        cout << p->getName() << " for placing a settlement please chose 3 tiles (to place between them)\n ";
        Tile *t1 = chooseTile(p->getGameManager());
        Tile *t2 = chooseTile(p->getGameManager());
        Tile *t3 = chooseTile(p->getGameManager());
        p->placeSettlement(t1, t2, t3, false);

    } else if (action == PLACE_CITY) {
        cout << p->getName() << " for placing a city please chose 3 tiles (to place between them)\n ";
        Tile *t1 = chooseTile(p->getGameManager());
        Tile *t2 = chooseTile(p->getGameManager());
        Tile *t3 = chooseTile(p->getGameManager());
        p->placeCity(t1, t2, t3, false);
    } else if (action == BUY_DEVELOPMENT_CARD) {
        std::cout << "You chose to buy a development card." << std::endl;
        p->buyDevelopmentCard();

    } else if (action == SEE_YOUR_DEVELOPMENT_CARD) {
        std::cout << "You chose to see your development cards." << std::endl;
        p->getDevelopmentCards();

    } else if (action == USE_DEVELOPMENT_CARD) {
        std::cout << "You chose to use a development card." << std::endl;
        std::cout << "please choose a development card to use:\n";
        vector<DevelopmentCard *> devCards = p->getDevelopmentCards();
        if (devCards.empty())
            cout << "you dont own any development cards" << endl;
        else {
            for (unsigned int i = 0; i < devCards.size(); ++i) {
                cout << "[" << i << "]: " << devCards[i]->getName() << endl;
            }
            int index = -1;
            cout << "enter thre development card index\n";
            cin >> index;
            if (index < 0 || index > devCards.size())
                cout << "invalid index\n";
            else
                p->useDevelopmentCard(devCards[(unsigned int) index]);
        }
    } else if (action == SEE_YOUR_RESOURCES) {
        std::cout << "You chose to see your resources." << std::endl;
        p->printResources();
    } else if (action == TRADE_WITH_PLAYERS) {
        std::cout << "You chose to trade with other players." << std::endl;
        int rToGive = -1;
        int hardToGet = -1;
        cout << "chose a resource to give(0 - brick, 1-iron, 2- wheat, 3-wood, 4-wool) " << endl;
        cin >> rToGive;
        cout << "chose a resource to get(0 - brick, 1-iron, 2- wheat, 3-wood, 4-wool) " << endl;
        cin >> hardToGet;
        int playerIndex = -1;
        cout << "chose a player to trade with (enter an index):\n";
        p->getGameManager()->printPlayers();
        cin >> playerIndex;

        Player *other = p->getGameManager()->getPlayer(playerIndex);

        if (other != nullptr && other != p) {
            p->trade(other, hardToGet, 1, rToGive, 1, true);
        } else {
            cout << "can't make that trade\n";
        }

    } else if (action == TRADE_WITH_THE_BANK) {
        cout << "You chose to trade with the bank." << std::endl;
        int rToGive = -1;
        int hardToGet = -1;
        cout << "chose a resource to give(0 - brick, 1-iron, 2- wheat, 3-wood, 4-wool) " << endl;
        cin >> rToGive;
        cout << "chose a resource to get(0 - brick, 1-iron, 2- wheat, 3-wood, 4-wool) " << endl;
        cin >> hardToGet;
        p->tradeWithTheBank(hardToGet, rToGive);

    } else if (action == TRADE_DEVELOPMENT_CARDS) {
        std::string wantedDC;
        std::string givenDC;
        int playerToTradeWith = -1;

        std::cout << "what development card would you like to GET? \n";
        std::cin >> wantedDC;
        std::cout << "what development card would you like to GIVE? \n";
        std::cin >> givenDC;

        cout << "who would you like to trade with? \n";
        p->getGameManager()->printPlayers();
        cin >> playerToTradeWith;
        Player * other = p->getGameManager()->getPlayer(playerToTradeWith);

        p->tradeDevelopmentCardForDevelopmentCard(wantedDC,other,givenDC, true);


    } else if (action == END_YOUR_TURN) {
        std::cout << "You chose to end your turn." << std::endl;
        p->endTurn();
        if (p->getGameManager()->isGameOver())
            return GAME_OVER;
        return NEXT_TURN;
    } else if (action == PRINT_BOARD) {
        std::cout << "You chose to print the board." << std::endl;
        p->getGameManager()->getBoard()->printBoard();
    } else if (action == SEE_YOUR_BOARD_PRESENT) {
        p->printBoardPresent();
    } else if (action == SEE_EVERYONE_BOARD_PRESENT) {
        p->getGameManager()->printBoardPresent();
    } else {
        std::cout << "Invalid choice. Please choose a number between 1 and 12." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return 0;
}

// a function to place the starting set up of the board presents of the players
void startGame(Catan *gm, int numOfPlayers) {
    for (int i = 0; i < numOfPlayers * StartingPlacing; ++i) { // twice for each player place a settlement and a road
        Player *p = gm->getPlayerTurn();

        //place a settlement
        int placed = -1;
        while (placed == -1) {
            cout << p->getName() << " for placing a settlement please chose 3 tiles (to place between them)\n ";
            Tile *t1 = chooseTile(gm);
            Tile *t2 = chooseTile(gm);
            Tile *t3 = chooseTile(gm);
            placed = p->placeSettlement(t1, t2, t3, true);
            if (placed == -1)
                cout << "please try again\n";
            else {
                gm->addResourcesTO(p, t1);
                gm->addResourcesTO(p, t2);
                gm->addResourcesTO(p, t3);
            }
        }


        placed = -1;
        //place a road
        while (placed == -1) {
            cout << p->getName() << " for placing a road please chose 2 tiles (to place between them)\n ";
            cout << p->getName() << " pay attention that the road have to be continues to your board present\n";
            Tile *t1 = chooseTile(gm);
            Tile *t2 = chooseTile(gm);
            placed = p->placeRoad(t1, t2);
            if (placed == -1)
                cout << "please try again\n";
        }

        p->endTurn();
    }
}