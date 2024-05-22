// 211344015 alonsuissa12@gmail.com
//
// Created by alon on 5/20/24.
//
#include "Player.hpp"

namespace ariel {
    int convertResourceToInt(std::string resourceTile1) {
        int resNum = -1;
        if (resourceTile1 == "brick" || resourceTile1 == "BRICK")
            resNum = 0;
        if (resourceTile1 == "iron" || resourceTile1 == "IRON")
            resNum = 1;
        if (resourceTile1 == "wheat" || resourceTile1 == "WHEAT")
            resNum = 2;
        if (resourceTile1 == "wood" || resourceTile1 == "WOOD")
            resNum = 3;
        if (resourceTile1 == "wool" || resourceTile1 == "WOOL")
            resNum = 4;
        return resNum;
    }

    Player::Player(Catan *gm) {
        // default name
        name = "Player " + std::to_string(Player::playerNum);
        Player::playerNum++;
        gameManager = gm;
        VictoryPoints = 0;
        numOfKnights = 0;

        //settlements:
        for (int i = 0; i < 5; ++i) {
            Settlement s = Settlement(this);//todo: new? and add destructor
            unusedSettlements.push_back(&s);
        }
        //cities
        for (int i = 0; i < 4; ++i) {
            City c = City(this); //todo: new? and add destructor
            unusedCities.push_back(&c);
        }
        //roads
        for (int i = 0; i < 15; ++i) {
            Road r = Road(this); //todo: new? and add destructor
            unusedRoads.push_back(&r);
        }
        for (int i = 0; i < 5; ++i) {
            resources[i] = 0;
        }

    }

    Player::Player(Catan *gm, std::string name) {
        // default name
        this->name = name;
        Player::playerNum++;
        gameManager = gm;
        VictoryPoints = 0;
        numOfKnights = 0;

        //settlements:
        for (int i = 0; i < 5; ++i) {
            Settlement s = Settlement(this);//todo: new? and add destructor
            unusedSettlements.push_back(&s);
        }
        //cities
        for (int i = 0; i < 5; ++i) {
            City c = City(this); //todo: new? and add destructor
            unusedCities.push_back(&c);
        }
        //roads
        for (int i = 0; i < 5; ++i) {
            Road r = Road(this); //todo: new? and add destructor
            unusedRoads.push_back(&r);
        }
        for (int i = 0; i < 5; ++i) {
            resources[i] = 0;
        }
    }

    int Player::rollDice() {

        static bool seeded = false;
        if (!seeded) {
            srand(static_cast<unsigned int>(time(0)));
            seeded = true;
        }

        // Generate a random integer between 1 and 6
        int d1 = (rand() % 5) + 1;
        int d2 = (rand() % 5) + 1;

        gameManager->diceRoll(d1 + d2);

        return d1 + d2;
    }


    bool operator==(const Player &p1, const Player &p2) {
        return (&p1 == &p2);
    }

    bool operator!=(const Player &p1, const Player &p2) {
        return !(p1 == p2);
    }

    int Player::placeRoad(int numTile1, int resourceTile1, int numTile2, int resourceTile2) {
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
        if (unusedRoads.size() == 0) {
            std::cout << " no more roads to use!" << std::endl;
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
        Road *r1 = unusedRoads.back();

        int ans = r1->place(*t1, *t2);
        if (ans == 0) {
            unusedRoads.pop_back();
            usedRoads.push_back(r1);
        }
        return ans;
    }


    int Player::placeSettlement(int numTile1, std::string resourceTile1, int numTile2, std::string resourceTile2,
                                int numTile3, std::string resourceTile3,bool start = false) {
        if (unusedSettlements.size() == 0) {
            std::cout << " no more settlements to use!" << std::endl;
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
        return placeSettlement(numTile1, resNum1, numTile2, resNum2, numTile3, resNum3,start);
    }

    int Player::placeSettlement(int numTile1, int resourceTile1, int numTile2, int resourceTile2, int numTile3,
                                int resourceTile3,bool start  = false) {
        if (unusedRoads.size() == 0) {
            std::cout << " no more settlements to use!" << std::endl;
            return -1;
        }
        Tile *t1 = gameManager->findTile(numTile1, resourceTile1);
        Tile *t2 = gameManager->findTile(numTile2, resourceTile2);
        Tile *t3 = gameManager->findTile(numTile3, resourceTile3);


        if (t1 == nullptr || t2 == nullptr || t3 == nullptr) {
            std::cout << " location doesn't exist\n";
            return -1;
        }
        return placeSettlement(t1, t2,t3,start);
    }

    int Player::placeSettlement(Tile *t1, Tile* t2, Tile* t3,bool start) {
        Settlement *s1 = unusedSettlements.back();

        int ans = s1->place(*t1, *t2, *t3,start);
        if (ans == 0) {
            unusedSettlements.pop_back();
             usedUrbanEntities.push_back(s1);
        }
        return ans;
    }

}
