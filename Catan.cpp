// 211344015 alonsuissa12@gmail.com
//
// Created by alon on 5/20/24.
//

#include "Resources.hpp"

namespace ariel {
    Catan::Catan(Player &p1, Player &p2, Player &p3) {
        playerTurn = (unsigned int) myChooseStartingPlayer();
        p1.joinGame(this);
        p2.joinGame(this);
        p3.joinGame(this);
        players.push_back(&p1);
        players.push_back(&p2);
        players.push_back(&p3);

        this->board = new Board();

    }

    Catan::~Catan() {
        delete board; // board allocated dynamically
    }

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

    Board *Catan::getBoard() {
        return board;
    }

    void Catan::printWinner() {
        for (Player *pp: players) {
            if (pp->VictoryPoints >= 10)
                std::cout << pp->name << " is the winner!" << std::endl;
        }
    }

    int Catan::myChooseStartingPlayer() {
        // Seed the random number generator
        srand(static_cast<unsigned int>(time(0)));

        // Generate a random integer between 0 and 2
        int randomInt = rand() % 3; // Generates a random number in the range [0, 2]

        return randomInt;
    }

    Player *Catan::chooseStartingPlayer() {
        return players[playerTurn];
    }

    // updates the players resourced according to the dice roll
    void Catan::diceRoll(int diceRoll) {
        for (Player *pp: players) {
            for (unsigned int i = 0; i < pp->usedUrbanEntities.size(); ++i) {

                if (pp->usedUrbanEntities[i]->neighborTileRight->number == diceRoll) {
                    pp->resources[pp->usedUrbanEntities[i]->neighborTileRight->getResource()] += pp->usedUrbanEntities[i]->numOfResources;
                }
                if (pp->usedUrbanEntities[i]->neighborTileLeft->number == diceRoll) {
                    pp->resources[pp->usedUrbanEntities[i]->neighborTileLeft->getResource()] += pp->usedUrbanEntities[i]->numOfResources;
                }
                if (pp->usedUrbanEntities[i]->neighborTileDown->number == diceRoll) {
                    pp->resources[pp->usedUrbanEntities[i]->neighborTileDown->getResource()] += pp->usedUrbanEntities[i]->numOfResources;
                }
            }
        }
    }

    Tile *Catan::findTile(int numTile, int resourceTile) {
        Tile *pt = board->findTile(numTile, resourceTile);
        return pt;
    }

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

    void Catan::nextTurn() {
        std::cout << players[playerTurn]->name << " done with his turn. \n";
        playerTurn = ((playerTurn + 1) % players.size());
        std::cout << "it's  " << players[playerTurn]->name << " turn now, roll the dice!\n";
    }

    Player *Catan::getPlayerTurn() {
        return players[playerTurn];
    }

    void Catan::win(Player &p) {
        std::cout << p.getName() << " is the WINNER!!!\n";
        std::cout << p.getName() << " (this object will not be available for another game. in order to play another game ,please crate a new object of catan)\n";
        delete this;
    }
}