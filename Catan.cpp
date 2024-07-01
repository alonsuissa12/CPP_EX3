// 211344015 alonsuissa12@gmail.com
//
// Created by alon on 5/20/24.
//

#include "Resources.hpp"

namespace ariel {
    // Constructor for the Catan game class
    Catan::Catan(Player &p1, Player &p2, Player &p3,bool constBoard) {
        playerTurn = (unsigned int) myChooseStartingPlayer();
        p1.joinGame(this);
        p2.joinGame(this);
        p3.joinGame(this);
        players.push_back(&p1);
        players.push_back(&p2);
        players.push_back(&p3);

        this->board = new Board(constBoard);

        gameOver = false;
    }

    // Destructor for the Catan game class
    Catan::~Catan() {
        delete board; // board allocated dynamically
    }

    // Implements the "Monopoly" action
    void Catan::monopole(Player *p, int resource) {
        int sum = 0;
        for (Player *playerOther: players) {
            if (playerOther != p) {
                sum += playerOther->resources[resource];
                playerOther->resources[resource] = 0;
            }
        }
        p->resources[resource] += sum;
    }

    // Returns a pointer to the game board
    Board *Catan::getBoard() {
        return board;
    }

    // Prints the name of the player who has won
    void Catan::printWinner() {
        for (Player *pp: players) {
            if (pp->VictoryPoints >= 10)
                std::cout << pp->name << " is the winner!" << std::endl;
        }
    }

    // Helper function to randomly select the starting player index
    int Catan::myChooseStartingPlayer() {
        // Seed the random number generator
        srand(static_cast<unsigned int>(time(0)));

        // Generate a random integer between 0 and 2
        int randomInt = rand() % 3; // Generates a random number in the range [0, 2]

        return randomInt;
    }

    // Returns a pointer to the current starting player
    Player *Catan::chooseStartingPlayer() {
        return players[playerTurn];
    }

    // updates the players resourced according to the dice roll
    void Catan::diceRoll(int diceRoll) {
        if (diceRoll != 7) {
            for (Player *pp: players) {
                for (unsigned int i = 0; i < pp->usedUrbanEntities.size(); ++i) {

                    if (!pp->usedUrbanEntities[i]->neighborTileRight->isSea &&
                        !pp->usedUrbanEntities[i]->neighborTileRight->isDesert) // if its a resource tile
                        if (pp->usedUrbanEntities[i]->neighborTileRight->number ==
                            diceRoll) { // if the tile number is rolled
                            // add the generated resources to the owner
                            pp->resources[pp->usedUrbanEntities[i]->neighborTileRight->getResource()] += pp->usedUrbanEntities[i]->numOfResources;
                        }
                    if (!pp->usedUrbanEntities[i]->neighborTileLeft->isSea &&
                        !pp->usedUrbanEntities[i]->neighborTileLeft->isDesert) // if its a resource tile
                        if (pp->usedUrbanEntities[i]->neighborTileLeft->number == diceRoll) {
                            pp->resources[pp->usedUrbanEntities[i]->neighborTileLeft->getResource()] += pp->usedUrbanEntities[i]->numOfResources;
                        }

                    if (!pp->usedUrbanEntities[i]->neighborTileDown->isSea &&
                        !pp->usedUrbanEntities[i]->neighborTileDown->isDesert) // if its a resource tile
                        if (pp->usedUrbanEntities[i]->neighborTileDown->number == diceRoll) {
                            pp->resources[pp->usedUrbanEntities[i]->neighborTileDown->getResource()] += pp->usedUrbanEntities[i]->numOfResources;

                        }
                }
            }
        } else { //rolled 7
            for (Player *pp: players) {
                int numOfCards = 0;
                int resourcesToDiscard = 0;
                for (unsigned int i = 0; i < 5; ++i) {
                    numOfCards += pp->resources[i];
                }
                if (numOfCards > 7) {
                    resourcesToDiscard = numOfCards / 2;
                    int discarded = 0;
                    int nextDiscard = -1;
                    while (discarded < resourcesToDiscard) {
                        std::cout << pp->name << ", you need to discard " << resourcesToDiscard - discarded;
                        std::cout << " more resources. please choose yor next resource to discard. \n";
                        std::cout
                                << "Enter the resource you would like to discard (0 - brick, 1-iron, 2- wheat, 3-wood, 4-wool)\n";
                        std::cin >> nextDiscard;
                        if (nextDiscard > 4 || nextDiscard < 0 || pp->resources[nextDiscard] == 0) {
                            std::cout << "invalid choice. pleas try again. NOTE:\n";
                            pp->printResources();
                        } else {
                            pp->resources[nextDiscard]--;
                            nextDiscard = -1;
                            discarded++;
                        }
                    }

                }
            }

        }
    }

    // Adds resources to a player based on a tile
    void Catan::addResourcesTO(Player *p, Tile *t) {
        if (!t->getIsSea() && !t->getIsDesert()) {
            int resource = t->getResource();
            p->resources[resource]++;
        }


    }

    // Finds a tile on the game board by number and resource type
    Tile *Catan::findTile(int numTile, int resourceTile) {
        Tile *pt = board->findTile(numTile, resourceTile);
        return pt;
    }

    // Allows a player to buy a random development card
    DevelopmentCard *Catan::buyDevelopmentCard() {
        DevelopmentCard *pdc;

        // Seed the random number generator
        srand(static_cast<unsigned int>(time(0)));

        // Generate a random number between 1 and 25
        int randomNumber = (rand() % 25) + 1;

        if (randomNumber <= 14) { // knight
            pdc = new Knight(this);
        }
        if (randomNumber > 14 && randomNumber <= 19) {// victory point
            pdc = new VictoryPoint(this);
        }
        if (randomNumber > 19 && randomNumber <= 21) {// roads build
            pdc = new RoadsBuild(this);
        }
        if (randomNumber > 21 && randomNumber <= 23) {// year of plenty
            pdc = new YearOfPlenty(this);
        }
        if (randomNumber > 23 && randomNumber <= 25) {// monopoly
            pdc = new Monopole(this);
        }
        return pdc;
    }

    // Moves to the next turn in the game
    void Catan::nextTurn() {
        std::cout << players[playerTurn]->name << " done with his turn. \n";
        playerTurn = ((playerTurn + 1) % players.size());
        std::cout << "it's  " << players[playerTurn]->name << " turn now, roll the dice!\n";
    }

    // Returns the player whose turn it is
    Player *Catan::getPlayerTurn() {
        return players[playerTurn];
    }

    // Declares a winner and updates that the game is over
    void Catan::win(Player &p) {
        std::cout << p.getName() << " is the WINNER!!!\n";
        gameOver = true;
    }

    // Returns true if the game is over
    bool Catan::isGameOver() { return gameOver; }

    // Prints the names of all players in the game
    void Catan::printPlayers() {
        for (unsigned int i = 0; i < players.size(); ++i) {
            std::cout << "[" << i << "]: " << players[i]->name << "\n";
        }
    }

    // Returns the player at the specified index
    Player *Catan::getPlayer(int x) {
        if (x < 0 || x >= players.size())
            std::cout << "invalid player index\n";
        else
            return players[(unsigned int) x];
        return nullptr;
    }

    void Catan::printBoardPresent(){
        for (Player * p:players) {
            p->printBoardPresent();
        }
    }
}