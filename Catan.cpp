// 211344015 alonsuissa12@gmail.com
//
// Created by alon on 5/20/24.
//

#include "Resources.hpp"

namespace ariel {
    Catan::Catan(Player &p1, Player &p2, Player &p3) {
        p1.gameManager = this;
        p2.gameManager = this;
        p3.gameManager = this;
        players.push_back(&p1);
        players.push_back(&p2);
        players.push_back(&p3);

        this->board = new Board(); //todo: add destructor

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

    Board* Catan::getBoard() {
        return board;
    }

    void Catan::printWinner() {
        for (Player *pp: players) {
            if (pp->VictoryPoints >= 10)
                std::cout << pp->name << " is the winner!" << std::endl;
        }
    }

    Player &Catan::ChooseStartingPlayer() {
        // Seed the random number generator
        srand(static_cast<unsigned int>(time(0)));

        // Generate a random integer between 0 and 2
        int randomInt = rand() % 3; // Generates a random number in the range [0, 2]

        return *players[(unsigned int) randomInt];
    }

    // updates the players resourced according to the dice roll
    void Catan::diceRoll(int diceRoll) {
        for (Player *pp: players){
            for (unsigned int i = 0; i < pp->usedUrbanEntities.size(); ++i) {

                if(pp->usedUrbanEntities[i]->neighborTileRight->number == diceRoll){
                    pp->resources[pp->usedUrbanEntities[i]->neighborTileRight->getResource()] += pp->usedUrbanEntities[i]->numOfResources;
                }
                if(pp->usedUrbanEntities[i]->neighborTileLeft->number == diceRoll){
                    pp->resources[pp->usedUrbanEntities[i]->neighborTileLeft->getResource()] += pp->usedUrbanEntities[i]->numOfResources;
                }
                if(pp->usedUrbanEntities[i]->neighborTileDown->number == diceRoll){
                    pp->resources[pp->usedUrbanEntities[i]->neighborTileDown->getResource()] += pp->usedUrbanEntities[i]->numOfResources;
                }
            }
        }
    }

    Tile *Catan::findTile(int numTile, int resourceTile) {
        Tile* pt = board -> findTile( numTile,  resourceTile);
        return pt;
    }

}