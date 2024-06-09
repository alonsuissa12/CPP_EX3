// 211344015 alonsuissa12@gmail.com
//
// Created by alon on 5/20/24.
//
#include "Resources.hpp"

namespace ariel {
    int Player::playerNum = 0;

    // This function constructs a Player object with default attributes and initializes resources and urban entities.
    // It assigns a default name and increments the player number.
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
        resources[WOOD] = StartingPlacing;
        resources[BRICK] = StartingPlacing;

    }

    // This function constructs a Player object with a specified name and initializes resources and urban entities.
    // It increments the player number.
    // Parameter:
    // - name: The name of the player.
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

    // Destructor for the Player class.
    // It deallocates all settlements, cities, roads, and development cards.
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

    // Assigns the Catan game manager to the player.
    // Parameter:
    // - gm: Pointer to the Catan game manager.
    void Player::joinGame(Catan *gm) {
        gameManager = gm;
    }

    // Simulates rolling two dice and returns their sum.
    // It also updates the game manager with the dice roll result, which will resolve the result for all players.
    // Returns:
    // - The sum of the two dice.
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

    // Overloaded equality operator for comparing two Player objects.
    bool operator==(const Player &p1, const Player &p2) {
        return (&p1 == &p2);
    }

    // Overloaded inequality operator for comparing two Player objects.
    bool operator!=(const Player &p1, const Player &p2) {
        return &p1 != &p2;;
    }

    // Places a road between two specified tiles on the board.
    // Parameters:
    // - numTile1, resourceTile1: Location of the first tile.
    // - numTile2, resourceTile2: Location of the second tile.
    // Returns:
    // - 0 if successful, -1 otherwise.
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

    // Places a road between two specified tiles on the board.
    // Parameters:
    // - numTile1, resourceTile1: Location of the first tile.
    // - numTile2, resourceTile2: Location of the second tile.
    // Returns:
    // - 0 if successful, -1 otherwise.
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

    // Places a road between two specified tiles on the board.
    // Parameters:
    // - t1, t2: Pointers to the first and second tiles.
    // Returns:
    // - 0 if successful, -1 otherwise.
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

        if (t1->getIsSea() && t2->getIsSea()) {
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

    // Places a settlement at the intersection of three specified tiles on the board.
    // Parameters:
    // - numTile1, resourceTile1: Location of the first tile.
    // - numTile2, resourceTile2: Location of the second tile.
    // - numTile3, resourceTile3: Location of the third tile.
    // - start: Flag indicating if it's the start of the game.
    // Returns:
    // - 0 if successful, -1 otherwise
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
        if ((resources[WOOD] < 1 || resources[BRICK] < 1 || resources[WHEAT] < 1 || resources[WOOL] < 1) && !start) {
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

    // Places a settlement at the intersection of three specified tiles on the board.
    // Parameters:
    // - numTile1, resourceTile1: Location of the first tile.
    // - numTile2, resourceTile2: Location of the second tile.
    // - numTile3, resourceTile3: Location of the third tile.
    // - start: Flag indicating if it's the start of the game.
    // Returns:
    // - 0 if successful, -1 otherwise.
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

    // Places a settlement at the intersection of three specified tiles on the board.
    // Parameters:
    // - t1, t2, t3: Pointers to the three tiles.
    // - start: Flag indicating if it's the start of the game.
    // Returns:
    // - 0 if successful, -1 otherwise.
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

    // Places a city at the intersection of three specified tiles on the board.
    // Parameters:
    // - numTile1, resourceTile1: Location of the first tile.
    // - numTile2, resourceTile2: Location of the second tile.
    // - numTile3, resourceTile3: Location of the third tile.
    // - start: Flag indicating if it's the start of the game.
    // Returns:
    // - 0 if successful, -1 otherwise.
    int Player::placeCity(int numTile1, std::string resourceTile1, int numTile2, std::string resourceTile2,
                          int numTile3, std::string resourceTile3, bool start = false) {
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


    // Places a city at the intersection of three specified tiles on the board.
    // Parameters:
    // - numTile1, resourceTile1: Location of the first tile.
    // - numTile2, resourceTile2: Location of the second tile.
    // - numTile3, resourceTile3: Location of the third tile.
    // - start: Flag indicating if it's the start of the game.
    // Returns:
    // - 0 if successful, -1 otherwise.
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

    // Places a city at the intersection of three specified tiles on the board.
    // Parameters:
    // - t1, t2, t3: Pointers to the three tiles.
    // - start: Flag indicating if it's the start of the game.
    // Returns:
    // - 0 if successful, -1 otherwise.
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

    // Buys a development card from the game manager.
    // Returns:
    // - 0 if successful, -1 otherwise.
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

    // Uses a development card.
    // Parameter:
    // - dc: Pointer to the development card to be used.
    // Returns:
    // - 0 if successful, -1 otherwise.
    int Player::useDevelopmentCard(DevelopmentCard *dc) {
        if(dc == nullptr){
            std::cout << name << "no card left \n";
            return -1;
        }
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

    // Retrieves the development cards owned by the player and prints them.
    // Returns:
    // - A vector containing pointers to the development cards.
    std::vector<DevelopmentCard *> Player::getDevelopmentCards() {
        if (*gameManager->getPlayerTurn() != *this) {
            std::cout << name << ", its not your turn! \n";
            return std::vector<DevelopmentCard *>(); // Return an empty vector;
        }
        std::cout << "development cards you (" << name << ") have: ";
        if (!developmentCards.empty()) {
            for (unsigned int i = 0; i < developmentCards.size() - 1; ++i) {
                std::cout << developmentCards[i]->getName() << ", ";
            }
            if (developmentCards.size() - 1 >= 0)
                std::cout << developmentCards[developmentCards.size() - 1]->getName();
            std::cout << "\n";
        } else {
            std::cout << "none \n";
        }
        return developmentCards;
    }

    int Player::getNumOfKnights() {
        return numOfKnights;
    }

    // Initiates a trade with another player.
    // Parameters:
    // - other: Pointer to the player to trade with.
    // - wantedResource: The type of resource wanted by the other player.
    // - wantedAmount: The amount of wanted resource.
    // - givenResource: The type of resource offered by the player initiating the trade.
    // - givenAmount: The amount of offered resource.
    // Returns:
    // - 0 if successful, -1 otherwise.
    int Player::trade(Player *other, int wantedResource, int wantedAmount, int givenResource, int givenAmount) {
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

    // Trade with the bank 4 resources for one resource
    // Parameters:
    // - wantedResource: The type of resource wanted from the bank.
    // - givenResource: The type of resource offered to the bank.
    // Returns:
    // - 0 if successful, -1 otherwise.
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

    // Retrieves the player's victory points.
    // Returns:
    // - The number of victory points.
    int Player::getVictoryPoints() { return VictoryPoints; }

    // Retrieves the player's name.
    // Returns:
    // - The name of the player.
    std::string Player::getName() { return name; }

    // Ends the player's turn by resetting the played development card flag and checking for victory conditions.
    void Player::endTurn() {
        playedDevelopmentCard = false;
        if (VictoryPoints >= 10) { //win game
            gameManager->win(*this);
        } else {
            gameManager->nextTurn();
            rolledDiceThisTurn = false;
        }
    }

    // Retrieves the game manager associated with the player.
    // Returns:
    // - Pointer to the Catan game manager.
    Catan *Player::getGameManager() {
        return gameManager;
    }

    // Prints the resources owned by the player.
    void Player::printResources() {
        std::cout << "resources of " << name << ": \n";
        std::cout << "      bricks- " << resources[BRICK] << "\n";
        std::cout << "      iron- " << resources[IRON] << "\n";
        std::cout << "      wheat- " << resources[WHEAT] << "\n";
        std::cout << "      wood- " << resources[WOOD] << "\n";
        std::cout << "      wool- " << resources[WOOL] << "\n";
    }

    // Retrieves whether the player has rolled the dice during their turn.
    // Returns:
    // - True if the player has rolled the dice, false otherwise.
    bool Player::getRolledDice() {
        return rolledDiceThisTurn;
    }

    // Moves a settlement from the usedUrbanEntities vector back to the unusedSettlements vector.
    // Parameter:
    // - ps: Pointer to the settlement to be taken back.
    void Player::takeBackSettlement(Settlement *ps) {
        for (unsigned int i = 0; i < usedUrbanEntities.size(); ++i) {
            if (usedUrbanEntities[i] == ps) {
                usedUrbanEntities.erase(usedUrbanEntities.begin() + i);
                unusedSettlements.push_back(ps);
            }
        }
    }

    void Player::printBoardPresent() {

        std::cout << "----- " << name << " ----- \n";
        std::cout << "--settlements:\n";
        for (unsigned int i = 0; i < usedUrbanEntities.size(); ++i) {
            if (usedUrbanEntities[i]->getType() == SETTLEMENT) {
                std::cout << *(usedUrbanEntities[i]->getNeighbor(0)) << ", ";
                std::cout << *(usedUrbanEntities[i]->getNeighbor(1)) << ", ";
                std::cout << *(usedUrbanEntities[i]->getNeighbor(2)) << "\n ";
            }
        }
        std::cout << "--cities:\n";
        for (unsigned int i = 0; i < usedUrbanEntities.size(); ++i) {
            if (usedUrbanEntities[i]->getType() == CITY) {
                std::cout << *(usedUrbanEntities[i]->getNeighbor(0)) << ", ";
                std::cout << *(usedUrbanEntities[i]->getNeighbor(1)) << ", ";
                std::cout << *(usedUrbanEntities[i]->getNeighbor(2)) << "\n ";
            }
        }
        std::cout << "--roads:\n";
        for (unsigned int i = 0; i < usedRoads.size(); ++i) {
            std::cout << *(usedRoads[i]->getNeighbor(0)) << ", ";
            std::cout << *(usedRoads[i]->getNeighbor(1)) << "\n";
        }

    }

    int Player::tradeDevelopmentCardForDevelopmentCard(
            std::string wantedDC, Player *other, std::string givedDC) {
        int agree = -1;
        for (unsigned int otherIndex = 0; otherIndex < other->developmentCards.size(); ++otherIndex) {
            DevelopmentCard *dcp = other->developmentCards[otherIndex];
            if (dcp->getName() == wantedDC) {
                for (unsigned int myIndex = 0; myIndex < developmentCards.size(); ++myIndex) {
                    DevelopmentCard *myDcp = this->developmentCards[myIndex];
                    if (myDcp->getName() == givedDC) {
                        std::cout << other->name << ", would you like to trade your " << wantedDC
                                  << " development card, for " << name << "'s " << givedDC
                                  << " development card? (type 1/0)\n";
                        std::cin >> agree;
                        while (agree != 0 && agree != 1) {
                            std::cin.clear(); // Clear error flags
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                            std::cout << " invailed answer please try again\n";
                            std::cout << other->name << ", would you like to trade your " << wantedDC
                                      << " development card, for " << name << "'s " << givedDC
                                      << " development card? (type 1/0)\n";
                        }
                        if (agree) {
                            // make trade
                            other->developmentCards.erase(other->developmentCards.begin() + otherIndex);
                            other->developmentCards.push_back(myDcp);

                            this->developmentCards.erase(this->developmentCards.begin() + myIndex);
                            this->developmentCards.push_back(dcp);
                            return 0;
                        } else {
                            std::cout << other->name << " has decline your offer \n";
                            return 1;
                        }
                    }
                }
                break;
            }
        }
        std::cout << "Don't have the right cards. cannot make the trade\n";
        return 0;
    }
}




