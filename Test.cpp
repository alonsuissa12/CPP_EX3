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

    // cur player placing on iron 11, iron 1,wood 4 and road on iron 3 wood 4
    CHECK((curPlayer->placeSettlement(11, IRON, 3, IRON, 4, WOOD, true) == 0));

    //cur player place a settlement on wool 6 brick 9 brick 10
    CHECK((curPlayer->placeSettlement(6, WOOL, 9, BRICK, 10, BRICK, true) == 0));

    //cur player place a settlement on wheat 10 wheat 11 desert
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
    DevelopmentCard *toUse = curPlayer->getDevelopmentCards().back();
    CHECK((curPlayer->useDevelopmentCard(toUse) == 0));
    CHECK((curPlayer->getNumOfKnights() == 1));

    i = 0;
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
    CHECK((curPlayer->useDevelopmentCard(toUse) == 0));
    CHECK_EQ(curPlayer->getVictoryPoints(), 1);

}
//
TEST_CASE("trade resources with players") {
    cout << "==================== trade resources with players =====================\n";

    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3, true); // constant board
    catan.chooseStartingPlayer();
    Player *wasCurPlayer = catan.getPlayerTurn();
    wasCurPlayer->endTurn();
    Player *curPlayer = catan.getPlayerTurn();

    // give resources to the players
    catan.addResourcesTO(wasCurPlayer, catan.getBoard()->findTile(6, WOOL));  // add wool to the current player
    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(11, IRON)); // add iron to the current player

    // trade in a good way
    CHECK((curPlayer->trade(wasCurPlayer, WOOL, 1, IRON, 1, false) == 0));
    CHECK((curPlayer->getResources()[WOOL] == 1));
    CHECK((curPlayer->getResources()[IRON] == 0));
    CHECK((wasCurPlayer->getResources()[WOOL] == 0));
    CHECK((wasCurPlayer->getResources()[IRON] == 1));

    //try to trade without enough resources
    CHECK((curPlayer->trade(wasCurPlayer, WHEAT, 1, IRON, 1, false) == -1));
    CHECK((curPlayer->getResources()[WHEAT] == 0));
    CHECK((curPlayer->getResources()[IRON] == 0));
    CHECK((wasCurPlayer->getResources()[WHEAT] == 0));
    CHECK((wasCurPlayer->getResources()[IRON] == 1));


}

TEST_CASE("trade with the bank") {
    cout << "==================== trade with the bank =====================\n";

    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3, true); // constant board
    catan.chooseStartingPlayer();
    Player *curPlayer = catan.getPlayerTurn();

    // give resources to the players
    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(11, IRON)); // add iron to the current player
    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(11, IRON)); // add iron to the current player
    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(11, IRON)); // add iron to the current player
    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(11, IRON)); // add iron to the current player

    CHECK((curPlayer->tradeWithTheBank(WOOL, IRON) == 0));
    CHECK((curPlayer->getResources()[IRON] == 0));
    CHECK((curPlayer->getResources()[WOOL] == 1));

    // try to trade without enough(4) resources
    CHECK((curPlayer->tradeWithTheBank(IRON, WHEAT) == -1));
    CHECK((curPlayer->getResources()[IRON] == 0));

}

TEST_CASE("trade development cards") {
    cout << "==================== trade development cards =====================\n";

    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3, true); // constant board
    catan.chooseStartingPlayer();
    Player *wasCurPlayer = catan.getPlayerTurn();

    string prevCardName = "";

    // prev player buying a development card
    catan.addResourcesTO(wasCurPlayer, catan.getBoard()->findTile(10, WHEAT));// add wheat to the current player
    catan.addResourcesTO(wasCurPlayer, catan.getBoard()->findTile(6, WOOL));  // add wool to the current player
    catan.addResourcesTO(wasCurPlayer, catan.getBoard()->findTile(11, IRON)); // add iron to the current player
    wasCurPlayer->buyDevelopmentCard();
    prevCardName = wasCurPlayer->getDevelopmentCards().front()->getName();

    wasCurPlayer->endTurn();
    Player *curPlayer = catan.getPlayerTurn();
    // current player buying a development card
    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(10, WHEAT));// add wheat to the current player
    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(6, WOOL));  // add wool to the current player
    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(11, IRON)); // add iron to the current player
    curPlayer->buyDevelopmentCard();
    string curCardName = curPlayer->getDevelopmentCards().front()->getName();


    CHECK((curPlayer->tradeDevelopmentCardForDevelopmentCard(prevCardName, wasCurPlayer, curCardName, false) == 0));
    auto curDevCards = curPlayer->getDevelopmentCards();
    auto prevDevCards = wasCurPlayer->getDevelopmentCards();
    CHECK((curDevCards.size() == 1));
    CHECK((prevDevCards.size() == 1));
    CHECK_EQ(prevCardName, curDevCards.front()->getName());
    CHECK_EQ(curCardName, prevDevCards.front()->getName());

}

TEST_CASE("end turn") {
    cout << "==================== end turn =====================\n";

    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3, true); // constant board
    catan.chooseStartingPlayer();
    Player *wasCurPlayer = catan.getPlayerTurn();
    wasCurPlayer->endTurn();
    Player *curPlayer = catan.getPlayerTurn();

    CHECK((curPlayer != wasCurPlayer));

}

TEST_CASE("end turn with win") {
    cout << "==================== end turn with win =====================\n";


    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3, true); // constant board
    catan.chooseStartingPlayer();
    Player *curPlayer = catan.getPlayerTurn();
    CHECK_EQ(catan.isGameOver(), false);
    int vpCounter = 0;

    while (vpCounter < 10) {
        catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(10, WHEAT));// add wheat to the current player
        catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(6, WOOL));  // add wool to the current player
        catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(11, IRON)); // add iron to the current player
        curPlayer->buyDevelopmentCard();
        if (curPlayer->getDevelopmentCards().back()->getName() == "VictoryPoint")
            vpCounter++;
        else
            this_thread::sleep_for(std::chrono::milliseconds(567));
        DEBUG("counter " << vpCounter );
    }

    for (DevelopmentCard *pdv: curPlayer->getDevelopmentCards()) {
        if (pdv->getName() == "VictoryPoint")
            curPlayer->useDevelopmentCard(pdv);
    }

    curPlayer->endTurn();
    CHECK_EQ(catan.isGameOver(), true);

}

TEST_CASE("roll dice") {
    cout << "==================== roll dice =====================\n";

    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3, true); // constant board
    catan.chooseStartingPlayer();

    // roll the dice
    for (int i = 0; i < 10; ++i) {
        int result =catan.getPlayerTurn()->rollDice();
        catan.getPlayerTurn()->endTurn();
        CHECK((result > 0 && result < 13));
    }
    // try to roll not on ur turn
    Player  * prevPlayer = catan.getPlayerTurn();
    catan.getPlayerTurn()->endTurn();
    Player  * curPlayer = catan.getPlayerTurn();
    CHECK_EQ(prevPlayer->rollDice(),-1);
}

TEST_CASE("roll dice effects"){
    cout << "==================== roll dice effects =====================\n";

    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3, true); // constant board
    catan.chooseStartingPlayer();
    Player *curPlayer = catan.getPlayerTurn();
    curPlayer->placeSettlement(10, WHEAT, 2, WHEAT, 5, DESERT, true);
    curPlayer->placeSettlement(9, WOOL, 10, WHEAT, 8, WOOL, true);
    int result = -1;
    int before = curPlayer->getResources()[WOOL];
    while(result != 8) {
        result = catan.getPlayerTurn()->rollDice();
        catan.getPlayerTurn()->endTurn();
        if(result == 7 )
            before = curPlayer->getResources()[WOOL];
    }
    CHECK_EQ(before + 1,curPlayer->getResources()[WOOL] );


}
