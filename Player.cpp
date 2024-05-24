// 211344015 alonsuissa12@gmail.com
//
// Created by alon on 5/20/24.
//
#include "Resources.hpp"

namespace ariel {
    int Player::playerNum = 0;


    Player::Player() {
        // default name
        name = "Player " + std::to_string(Player::playerNum);
        Player::playerNum++;
        VictoryPoints = 0;
        numOfKnights = 0;
        playedDevelopmentCard = false;
        rolledDiceThisTurn = false;

        //settlements:
        for (int i = 0; i < 5; ++i) {
            Settlement *s = new Settlement(this);
            unusedSettlements.push_back(s);
        }
        //cities
        for (int i = 0; i < 4; ++i) {
            City *c = new City(this);
            unusedCities.push_back(c);
        }
        //roads
        for (int i = 0; i < 15; ++i) {
            Road *r = new Road(this);
            unusedRoads.push_back(r);
        }
        for (int i = 0; i < 5; ++i) {
            resources[i] = 0;
        }
        //for placing the roads at the start of the game
        resources[WOOD] = 2;
        resources[BRICK] = 2;

    }

    Player::Player(std::string name) {
        // default name
        this->name = name;
        Player::playerNum++;
        VictoryPoints = 0;
        numOfKnights = 0;
        playedDevelopmentCard = false;
        rolledDiceThisTurn = false;

        //settlements:
        for (int i = 0; i < 5; ++i) {
            Settlement *s = new Settlement(this);
            unusedSettlements.push_back(s);
        }
        //cities
        for (int i = 0; i < 5; ++i) {
            City *c = new City(this);
            unusedCities.push_back(c);
        }
        //roads
        for (int i = 0; i < 5; ++i) {
            Road *r = new Road(this);
            unusedRoads.push_back(r);
        }
        for (int i = 0; i < 5; ++i) {
            resources[i] = 0;
        }

        //for placing the roads at the start of the game
        resources[WOOD] = 2;
        resources[BRICK] = 2;

    }

    Player::~Player() {
        // Deallocate settlements
        for (Settlement *s: unusedSettlements) {
            delete s;
        }
        // Deallocate cities
        for (City *c: unusedCities) {
            delete c;
        }
        // Deallocate roads
        for (Road *r: unusedRoads) {
            delete r;
        }

        for (Road *r: usedRoads) {
            delete r;
        }

        for (UrbanEntity *u: usedUrbanEntities) {
            delete u;
        }

        for (DevelopmentCard *dc: developmentCards) {
            delete dc;
        }


    }


    void Player::joinGame(Catan *gm) {
        gameManager = gm;
    }

    int Player::rollDice() {
        if (*gameManager->getPlayerTurn() != *this) {
            std::cout << name << ", its not your turn! \n";
            return -1;
        }
        static bool seeded = false;
        if (!seeded) {
            srand(static_cast<unsigned int>(time(0)));
            seeded = true;
        }

        // Generate a random integer between 1 and 6
        int d1 = (rand() % 5) + 1;
        int d2 = (rand() % 5) + 1;

        std::cout << name << " rolled " << d1 + d2 << "\n";
        gameManager->diceRoll(d1 + d2);
        rolledDiceThisTurn = true;
        return d1 + d2;
    }


    bool operator==(Player &p1, Player &p2) {
        return (&p1 == &p2);
    }

    bool operator!=(const Player &p1, const Player &p2) {
        return &p1 != &p2;;
    }

    int Player::placeRoad(int numTile1, int resourceTile1, int numTile2, int resourceTile2) {
        if (*gameManager->getPlayerTurn() != *this) {
            std::cout << name << ", its not your turn! \n";
            return -1;
        }
        if (unusedRoads.size() == 0) {
            std::cout << " no more roads to use!" << std::endl;
            return -1;
        } else {
            Tile *t1 = gameManager->findTile(numTile1, resourceTile1);
            Tile *t2 = gameManager->findTile(numTile2, resourceTile2);

            if (t1 == nullptr || t2 == nullptr) {
                std::cout << " location doesn't exist\n";
                return -1;
            }
            return placeRoad(t1, t2);

        }
        return 0;
    }

    int Player::placeRoad(int numTile1, std::string resourceTile1, int numTile2, std::string resourceTile2) {
        if (*gameManager->getPlayerTurn() != *this) {
            std::cout << name << ", its not your turn! \n";
            return -1;
        }
        if (unusedRoads.size() == 0) {
            std::cout << " no more roads to use!" << std::endl;
            return -1;
        }
        if (resources[WOOD] < 1 || resources[BRICK] < 1) {
            std::cout << " not enough resources!" << std::endl;
            return -1;
        }


        int resNum1 = convertResourceToInt(resourceTile1);
        int resNum2 = convertResourceToInt(resourceTile2);

        if (resNum2 == -1 || resNum1 == -1) {
            std::cout << " wrong resource name. make sure you use one of the resources:" << std::endl;
            std::cout << "brick, iron, wheat, wood, wool " << std::endl;
            return -1;
        }

        return placeRoad(numTile1, resNum1, numTile2, resNum2);

    }

    int Player::placeRoad(Tile *t1, Tile *t2) {
        if (*gameManager->getPlayerTurn() != *this) {
            std::cout << name << ", its not your turn! \n";
            return -1;
        }
        if (resources[WOOD] < 1 || resources[BRICK] < 1) {
            std::cout << " not enough resources!" << std::endl;
            return -1;
        }

        if (resources[WOOD] < 1 || resources[BRICK] < 1) {
            std::cout << " not enough resources!" << std::endl;
            return -1;
        }

        if(t1->getIsSea() && t2->getIsSea()){
            std::cout << " cant place a road between two sea tiles" << std::endl;
            return -1;
        }

        Road *r1 = unusedRoads.back();

        int ans = r1->place(*t1, *t2);
        if (ans == 0) {
            unusedRoads.pop_back();
            usedRoads.push_back(r1);
            resources[WOOD]--;
            resources[BRICK]--;
        }
        return ans;
    }


    int Player::placeSettlement(int numTile1, std::string resourceTile1, int numTile2, std::string resourceTile2,
                                int numTile3, std::string resourceTile3, bool start = false) {
        if (*gameManager->getPlayerTurn() != *this) {
            std::cout << name << ", its not your turn! \n";
            return -1;
        }
        if (unusedSettlements.size() == 0) {
            std::cout << " no more settlements to use!" << std::endl;
            return -1;
        }
        if ((resources[WOOD] < 1 || resources[BRICK] < 1 || resources[WHEAT] < 1 || resources[WOOL] < 1)&&!start) {
            std::cout << " not enough resources!" << std::endl;
            return -1;
        }

        int resNum1 = convertResourceToInt(resourceTile1);
        int resNum2 = convertResourceToInt(resourceTile2);
        int resNum3 = convertResourceToInt(resourceTile3);

        if (resNum2 == -1 || resNum1 == -1 || resNum3 == -1) {
            std::cout << " wrong resource name. make sure you use one of the resources:" << std::endl;
            std::cout << "brick, iron, wheat, wood, wool " << std::endl;
            return -1;
        }
        return placeSettlement(numTile1, resNum1, numTile2, resNum2, numTile3, resNum3, start);
    }

    int Player::placeSettlement(int numTile1, int resourceTile1, int numTile2, int resourceTile2, int numTile3,
                                int resourceTile3, bool start = false) {
        if (*gameManager->getPlayerTurn() != *this) {
            std::cout << name << ", its not your turn! \n";
            return -1;
        }
        if (unusedSettlements.size() == 0) {
            std::cout << " no more settlements to use!" << std::endl;
            return -1;
        }
        if ((resources[WOOD] < 1 || resources[BRICK] < 1 || resources[WHEAT] < 1 || resources[WOOL] < 1) && !start) {
            std::cout << " not enough resources!" << std::endl;
            return -1;
        }

        Tile *t1 = gameManager->findTile(numTile1, resourceTile1);
        Tile *t2 = gameManager->findTile(numTile2, resourceTile2);
        Tile *t3 = gameManager->findTile(numTile3, resourceTile3);


        if (t1 == nullptr || t2 == nullptr || t3 == nullptr) {
            std::cout << " location doesn't exist\n";
            return -1;
        }
        return placeSettlement(t1, t2, t3, start);
    }

    int Player::placeSettlement(Tile *t1, Tile *t2, Tile *t3, bool start) {
        if (*gameManager->getPlayerTurn() != *this) {
            std::cout << name << ", its not your turn! \n";
            return -1;
        }
        if ((resources[WOOD] < 1 || resources[BRICK] < 1 || resources[WHEAT] < 1 || resources[WOOL] < 1) && !start) {
            std::cout << " not enough resources!" << std::endl;
            return -1;
        }
        if (unusedSettlements.size() == 0) {
            std::cout << " no more settlements to use!" << std::endl;
            return -1;
        }
        Settlement *s1 = unusedSettlements.back();

        int ans = s1->place(*t1, *t2, *t3, start);
        if (ans == 0) {
            unusedSettlements.pop_back();
            usedUrbanEntities.push_back(s1);
            VictoryPoints++;
            if (!start) {
                resources[WOOD]--;
                resources[BRICK]--;
                resources[WHEAT]--;
                resources[WOOL]--;
            }
        }
        return ans;
    }

    int
    Player::placeCity(int numTile1, std::string resourceTile1, int numTile2, std::string resourceTile2, int numTile3,
                      std::string resourceTile3, bool start = false) {
        if (*gameManager->getPlayerTurn() != *this) {
            std::cout << name << ", its not your turn! \n";
            return -1;
        }
        if (unusedCities.size() == 0) {
            std::cout << " no more Cities to use!" << std::endl;
            return -1;
        }
        if (resources[IRON] < 3 || resources[WHEAT] < 2) {
            std::cout << " not enough resources!" << std::endl;
            return -1;
        }

        int resNum1 = convertResourceToInt(resourceTile1);
        int resNum2 = convertResourceToInt(resourceTile2);
        int resNum3 = convertResourceToInt(resourceTile3);

        if (resNum2 == -1 || resNum1 == -1 || resNum3 == -1) {
            std::cout << " wrong resource name. make sure you use one of the resources:" << std::endl;
            std::cout << "brick, iron, wheat, wood, wool " << std::endl;
            return -1;
        }
        return placeCity(numTile1, resNum1, numTile2, resNum2, numTile3, resNum3, start);
    }

    int Player::placeCity(int numTile1, int resourceTile1, int numTile2, int resourceTile2, int numTile3,
                          int resourceTile3, bool start = false) {
        if (*gameManager->getPlayerTurn() != *this) {
            std::cout << name << ", its not your turn! \n";
            return -1;
        }
        if (resources[IRON] < 3 || resources[WHEAT] < 2) {
            std::cout << " not enough resources!" << std::endl;
            return -1;
        }
        if (unusedCities.size() == 0) {
            std::cout << " no more cities to use!" << std::endl;
            return -1;
        }
        Tile *t1 = gameManager->findTile(numTile1, resourceTile1);
        Tile *t2 = gameManager->findTile(numTile2, resourceTile2);
        Tile *t3 = gameManager->findTile(numTile3, resourceTile3);


        if (t1 == nullptr || t2 == nullptr || t3 == nullptr) {
            std::cout << " location doesn't exist\n";
            return -1;
        }
        return placeCity(t1, t2, t3, start);
    }

    int Player::placeCity(Tile *t1, Tile *t2, Tile *t3, bool start) {
        if (*gameManager->getPlayerTurn() != *this) {
            std::cout << name << ", its not your turn! \n";
            return -1;
        }
        City *c1 = unusedCities.back();
        if (resources[IRON] < 3 || resources[WHEAT] < 2) {
            std::cout << " not enough resources!" << std::endl;
            return -1;
        }

        int ans = c1->place(*t1, *t2, *t3, start);
        if (ans == 0) {
            unusedCities.pop_back();
            usedUrbanEntities.push_back(c1);
            VictoryPoints++;
            resources[WHEAT] -= 2;
            resources[IRON] -= 3;
        }
        return ans;
    }

    int Player::buyDevelopmentCard() {
        if (*gameManager->getPlayerTurn() != *this) {
            std::cout << name << ", its not your turn! \n";
            return -1;
        }
        if (resources[IRON] < 1 || resources[WOOL] < 1 || resources[WHEAT] < 1) {
            std::cout << " not enough resources!" << std::endl;
            return -1;
        }
        DevelopmentCard *pdvc = gameManager->buyDevelopmentCard();
        if (pdvc != nullptr) {

            std::cout << name << " bought " << pdvc->getName() << " card\n";
            developmentCards.push_back(pdvc);
            resources[IRON]--;
            resources[WOOL]--;
            resources[WHEAT]--;

            return 0;
        }
        return -1;
    }

    int Player::useDevelopmentCard(DevelopmentCard *dc) {
        if (*gameManager->getPlayerTurn() != *this) {
            std::cout << name << ", its not your turn! \n";
            return -1;
        }
        bool isVP = dc->getName() == "VictoryPoint";
        if (!isVP && playedDevelopmentCard) {
            std::cout << "you can only play one development card per turn (except of victory points)\n ";
            return -1;
        }

        auto it = std::find(developmentCards.begin(), developmentCards.end(), dc);
        // If dc is found, erase it from the vector
        if (it != developmentCards.end()) {
            dc->playCard(*this);
            developmentCards.erase(it);
            if (!isVP)
                playedDevelopmentCard = true;
            delete dc; // delete the card because it's dynamically allocated
            return 0;
        } else {
            std::cout << "Invalid development card!\n";
            return -1;
        }
    }

    std::vector<DevelopmentCard *> Player::getDevelopmentCards() {
        if (*gameManager->getPlayerTurn() != *this) {
            std::cout << name << ", its not your turn! \n";
            return std::vector<DevelopmentCard *>(); // Return an empty vector;
        }
        std::cout << "development cards you (" << name << ") have: ";
        if(!developmentCards.empty()) {
            for (unsigned int i = 0; i < developmentCards.size() - 1; ++i) {
                std::cout << developmentCards[i]->getName() << ", ";
            }
            if (developmentCards.size() - 1 >= 0)
                std::cout << developmentCards[developmentCards.size() - 1]->getName();
            std::cout << "\n";
        }
        else{
            std::cout << "none \n";
        }
        return developmentCards;
    }

    int Player::trade(Player* other, int wantedResource, int wantedAmount, int givenResource, int givenAmount) {
        if (*gameManager->getPlayerTurn() != *this) {
            std::cout << name << ", its not your turn! \n";
            return -1;
        }
        if (wantedResource > 4 || wantedResource < 0 || givenResource > 4 || givenResource < 0) {
            std::cout << "Invalid resource numbers\n";
            return -1;
        }
        if (other->resources[wantedResource] < wantedAmount || resources[givenResource] < givenAmount) {
            std::cout << "not enough resources!\n";
            return -1;
        }


        int agree = 3;
        std::string wantedResourceString = convertResourceToString(wantedResource);
        std::string givenResourceString = convertResourceToString(givenResource);
        std::cout << "trade offer from " << name << " to " << other->name << " :\n";
        std::cout << "offers " << givenAmount << " " << givenResourceString << " in return for: " << wantedAmount << " "
                  << wantedResourceString << " \n";
        while (agree != 0 && agree != 1) {
            std::cout << other->name << " do you accept this offer? (enter 1/0 for yes/no)\n";
            agree++;
            std::cin >> agree;
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }
        if (agree == 1) {
            std::cout << other->name << " accepts your offer\n";
            other->resources[givenResource] += givenAmount;
            other->resources[wantedResource] -= wantedAmount;
            resources[wantedResource] += wantedAmount;
            resources[givenResource] -= givenAmount;
        } else {
            std::cout << other->name << " declined your offer\n";
        }
        return 0;

    }

    // trade with the bank 4 resources for one resource
    int Player::tradeWithTheBank(int wantedResource, int givenResource) {
        if (*gameManager->getPlayerTurn() != *this) {
            std::cout << name << ", its not your turn! \n";
            return -1;
        }
        if (wantedResource > 4 || wantedResource < 0 || givenResource > 4 || givenResource < 0) {
            std::cout << "Invalid resource numbers\n";
            return -1;
        }
        if (resources[givenResource] < 4) {
            std::cout << "not enough resources!\n";
            return -1;
        }
        resources[wantedResource]++;
        resources[givenResource] -= 4;

        std::string Wresource = convertResourceToString(wantedResource);
        std::string Gresource = convertResourceToString(givenResource);

        std::cout << name << " traded with the bank 4 " << Gresource << " for 1 " << Wresource << "\n";
        return 0;

    }

    int Player::getVictoryPoints() { return VictoryPoints; }

    std::string Player::getName() { return name; }

    void Player::endTurn() {
        playedDevelopmentCard = false;
        if (VictoryPoints >= 10) { //win game
            gameManager->win(*this);
        } else {
            gameManager->nextTurn();
            rolledDiceThisTurn = false;
        }
    }

    Catan *Player::getGameManager() {
        return gameManager;
    }
    void Player::printResources() {
        std::cout << "resources of " << name << ": \n";
        std::cout << "      bricks- " << resources[BRICK] << "\n";
        std::cout << "      iron- " << resources[IRON] << "\n";
        std::cout << "      wheat- " << resources[WHEAT] << "\n";
        std::cout << "      wood- " << resources[WOOD] << "\n";
        std::cout << "      wool- " << resources[WOOL] << "\n";
    }

    bool Player::getRolledDice() {
        return rolledDiceThisTurn;
    }
    void Player::takeBackSettlement(Settlement * ps) {
        for (unsigned int i = 0; i < usedUrbanEntities.size(); ++i) {
            if(usedUrbanEntities[i] == ps){
                usedUrbanEntities.erase(usedUrbanEntities.begin()+i);
                unusedSettlements.push_back(ps);
            }
        }
    }

}

