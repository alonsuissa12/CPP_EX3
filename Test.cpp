// 211344015 alonsuissa12@gmail.com
// Created by alon on 5/28/24.
//
// todo: tests!
#include "doctest.h"
#include "Resources.hpp"
#include <thread>       // For std::this_thread::sleep_for
#include <chrono>

using namespace ariel;
using namespace std;
using namespace doctest;


TEST_CASE("place settlement/road") {
    cout << "==================== place settlement =====================\n";

    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3, true); // constant board
    catan.chooseStartingPlayer();
    Player *curPlayer = catan.getPlayerTurn();

    // try to place settlement (using resources) without enough resources
    CHECK((curPlayer->placeSettlement(8, BRICK, 10, WHEAT, 9, WOOL, false) == -1));

    // p1 placing on iron 11, iron 1,wood 4 and road on iron 3 wood 4
    CHECK((curPlayer->placeSettlement(11, IRON, 3, IRON, 4, WOOD, true) == 0));

    //p1 place a settlement on wool 6 brick 9 brick 10
    CHECK((curPlayer->placeSettlement(6, WOOL, 9, BRICK, 10, BRICK, true) == 0));

    //p1 place a settlement on wheat 10 wheat 11 desert
    CHECK((curPlayer->placeSettlement(10, WHEAT, 11, WHEAT, 5, DESERT, true) == 0));

    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(10, BRICK));  // add brick to the current player
    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(10, BRICK));  // add brick to the current player
    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(10, BRICK));  // add brick to the current player

    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(11, IRON));  // add iron to the current player

    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(10, WHEAT));  // add wheat to the current player

    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(4, WOOD));  // add wood to the current player
    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(4, WOOD));  // add wood to the current player
    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(4, WOOD));  // add wood to the current player

    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(6, WOOL));  // add wool to the current player


    //try to place on taken spot
    CHECK((curPlayer->placeSettlement(10, WHEAT, 11, WHEAT, 5, DESERT, false) == -1));

    //try to place only one edge away from another settlement
    CHECK((curPlayer->placeSettlement(13, SEA, 11, WHEAT, 5, DESERT, false) == -1));

    // placing a settlement not on the start of the game without roads (not continues)
    CHECK((curPlayer->placeSettlement(10, WHEAT, 2, WHEAT, 5, DESERT, false) == -1));

    cout << "-----------\n";
    // try to place settlement not on the start of the game in a good way
    curPlayer->placeRoad(10, WHEAT, 5, DESERT);
    curPlayer->placeRoad(5, DESERT, 2, WHEAT);
    CHECK((curPlayer->placeSettlement(2, WHEAT, 5, DESERT, 16, SEA, false) == 0));

}

TEST_CASE("place city") {
    cout << "==================== place city =====================\n";
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3, true); // constant board
    catan.chooseStartingPlayer();
    Player *curPlayer = catan.getPlayerTurn();


    // try to place city without resources and without settlement first
    CHECK((curPlayer->placeCity(8, BRICK, 10, WHEAT, 9, WOOL, false) == -1));


    //  add 3 iron to the current player
    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(11, IRON));
    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(11, IRON));
    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(11, IRON));

    // add 2 wheat to the current player
    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(10, WHEAT));
    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(10, WHEAT));

    // try to place city without settlement first
    CHECK((curPlayer->placeCity(8, BRICK, 10, WHEAT, 9, WOOL, false) == -1));


    // place settlement to upgrade to city
    CHECK((curPlayer->placeSettlement(2, WHEAT, 5, DESERT, 16, SEA, true) == 0));

    //upgrade to city
    CHECK((curPlayer->placeCity(2, WHEAT, 5, DESERT, 16, SEA, false) == 0));

}

TEST_CASE("buy a development card") {
    cout << "==================== buy a development card =====================\n";

    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3, true); // constant board
    catan.chooseStartingPlayer();
    Player *curPlayer = catan.getPlayerTurn();

    // try to buy without enough resources
    CHECK((curPlayer->buyDevelopmentCard() == -1));


    //buy a development card
    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(10, WHEAT));// add wheat to the current player
    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(6, WOOL));  // add wool to the current player
    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(11, IRON)); // add iron to the current player
    CHECK((curPlayer->buyDevelopmentCard() == 0));
    CHECK((curPlayer->getDevelopmentCards().size() == 1));


}

TEST_CASE("use your development cards") {
    cout << "==================== use your development cards =====================\n";

    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3, true); // constant board
    catan.chooseStartingPlayer();
    Player *curPlayer = catan.getPlayerTurn();

    //buy 2 development card
    string cardName = "";
    unsigned int i = 0;
    while (cardName != "Knight") { // doesn't want the test to ask for input
        catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(10, WHEAT));// add wheat to the current player
        catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(6, WOOL));  // add wool to the current player
        catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(11, IRON)); // add iron to the current player
        curPlayer->buyDevelopmentCard();
        cardName = curPlayer->getDevelopmentCards()[i]->getName();
        i++;
        std::this_thread::sleep_for(std::chrono::milliseconds(567));
    }

    // use knight
    DevelopmentCard * toUse = curPlayer->getDevelopmentCards().back();
    CHECK((curPlayer->useDevelopmentCard(toUse)==0));
    CHECK((curPlayer->getNumOfKnights() == 1));

    i=0;
    while (cardName != "VictoryPoint") { // doesn't want the test to ask for input
        catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(10, WHEAT));// add wheat to the current player
        catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(6, WOOL));  // add wool to the current player
        catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(11, IRON)); // add iron to the current player
        curPlayer->buyDevelopmentCard();
        cardName = curPlayer->getDevelopmentCards()[i]->getName();
        i++;
        std::this_thread::sleep_for(std::chrono::milliseconds(567));
    }
    toUse = curPlayer->getDevelopmentCards().back();
    CHECK((curPlayer->useDevelopmentCard(toUse)==0));
    CHECK((curPlayer->getVictoryPoints() == 1));

}
//
//TEST_CASE(){}
//
//TEST_CASE(){}
//
//TEST_CASE(){}
//
//TEST_CASE(){}

