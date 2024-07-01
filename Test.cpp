// 211344015 alonsuissa12@gmail.com
// Created by alon on 5/28/24.
//
#include "doctest.h"
#include "Resources.hpp"
#include <thread>       // For std::this_thread::sleep_for
#include <chrono>
#include <iostream>
#include <sstream>

using namespace ariel;
using namespace std;
using namespace doctest;


TEST_CASE("Player default constructor - name") {
    cout << "==================== Player default constructor - name =====================\n";

    ariel::Player player;
    CHECK(player.getName() == "Player 0");
}

TEST_CASE("Player default constructor - VP") {
    cout << "==================== Player default constructor - VP =====================\n";
    ariel::Player player;
    CHECK((player.getVictoryPoints() == 0));
}

TEST_CASE("Player default constructor - Knights") {
    cout << "==================== Player default constructor - Knights =====================\n";

    ariel::Player player;
    CHECK((player.getNumOfKnights() == 0));
}

TEST_CASE("Player default constructor - has played DC") {
    cout << "==================== Player default constructor - has played DC =====================\n";

    ariel::Player player;
    CHECK((player.hasPlayedDevelopmentCard() == false));
}

TEST_CASE("Player default constructor - rolled dice") {
    cout << "==================== Player default constructor - rolled dice =====================\n";

    ariel::Player player;
    CHECK((player.getRolledDice() == false));
}

TEST_CASE("Player default constructor - starting resources") {
    cout << "==================== Player default constructor - starting resources =====================\n";

    ariel::Player player;
    const int *resources = player.getResources();
    for (int i = 0; i < 5; ++i) {
        if (i == WOOD || i == BRICK) {
            CHECK((resources[i] == StartingPlacing));
        } else {
            CHECK((resources[i] == 0));
        }
    }
}

TEST_CASE("Player name constructor - name") {
    cout << "==================== Player name constructor - name =====================\n";

    ariel::Player player("Alon");
    CHECK(player.getName() == "Alon");
}

TEST_CASE("Player name constructor - VP") {
    cout << "==================== Player name constructor - VP =====================\n";

    ariel::Player player("Alon");
    CHECK((player.getVictoryPoints() == 0));
}

TEST_CASE("Player name constructor - Knights") {
    cout << "==================== Player name constructor - Knight =====================\n";

    ariel::Player player("Alon");
    CHECK((player.getNumOfKnights() == 0));
}

TEST_CASE("Player name constructor - has played DC") {
    cout << "==================== Player name constructor - has played DC =====================\n";

    ariel::Player player("Alon");
    CHECK((player.hasPlayedDevelopmentCard() == false));
}

TEST_CASE("Player name constructor - rolled dice") {
    cout << "==================== Player name constructor - rolled dice =====================\n";

    ariel::Player player("Alon");
    CHECK((player.getRolledDice() == false));
}

TEST_CASE("Player name constructor - starting resources") {
    cout << "==================== Player name constructor - starting resources =====================\n";

    ariel::Player player("Alon");
    const int *resources = player.getResources();
    for (int i = 0; i < 5; ++i) {
        if (i == WOOD || i == BRICK) {
            CHECK((resources[i] == StartingPlacing));
        } else {
            CHECK((resources[i] == 0));
        }
    }
}


TEST_CASE("place settlement - start of game") {
    cout << "==================== place settlement - start of game =====================\n";

    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3, true); // constant board
    catan.chooseStartingPlayer();
    Player *curPlayer = catan.getPlayerTurn();

    // cur player placing on iron 11, iron 1,wood 4 and road on iron 3 wood 4
    CHECK((curPlayer->placeSettlement(11, IRON, 3, IRON, 4, WOOD, true) == 0));

    //cur player place a settlement on wool 6 brick 9 brick 10
    CHECK((curPlayer->placeSettlement(6, WOOL, 9, BRICK, 10, BRICK, true) == 0));

    //cur player place a settlement on wheat 10 wheat 11 desert
    CHECK((curPlayer->placeSettlement(10, WHEAT, 11, WHEAT, 5, DESERT, true) == 0));


}

TEST_CASE("place settlement - during game") {
    cout << "==================== place settlement - during game =====================\n";

    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3, true); // constant board
    catan.chooseStartingPlayer();
    Player *curPlayer = catan.getPlayerTurn();

    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(10, WHEAT));// add wheat to the current player
    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(6, WOOL));  // add wool to the current player
    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(3, WOOD)); // add wood to the current player
    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(8, BRICK)); // add iron to the current player

    //cur player place a settlement on wheat 10 wheat 11 desert (start game)
    CHECK((curPlayer->placeSettlement(10, WHEAT, 11, WHEAT, 5, DESERT, true) == 0));


    // try to place settlement not on the start of the game in a good way
    curPlayer->placeRoad(10, WHEAT, 5, DESERT);
    curPlayer->placeRoad(5, DESERT, 2, WHEAT);
    CHECK((curPlayer->placeSettlement(2, WHEAT, 5, DESERT, 16, SEA, false) == 0));

}

TEST_CASE("place settlement -  not continues") {
    cout << "==================== place not continues =====================\n";

    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3, true); // constant board
    catan.chooseStartingPlayer();
    Player *curPlayer = catan.getPlayerTurn();

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


    // placing a settlement not on the start of the game without roads (not continues)
    CHECK((curPlayer->placeSettlement(10, WHEAT, 2, WHEAT, 5, DESERT, false) == -1));
}

TEST_CASE("place settlement - taken spot") {
    cout << "==================== place settlement - taken spot =====================\n";

    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3, true); // constant board
    catan.chooseStartingPlayer();
    Player *curPlayer = catan.getPlayerTurn();

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

}

TEST_CASE("place settlement - not far enough") {
    cout << "==================== place settlement - not far enough =====================\n";

    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3, true); // constant board
    catan.chooseStartingPlayer();
    Player *curPlayer = catan.getPlayerTurn();

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


    //try to place only one edge away from another settlement
    CHECK((curPlayer->placeSettlement(13, SEA, 11, WHEAT, 5, DESERT, false) == -1));

}

TEST_CASE("placeSettlement with invalid tiles") {
    ariel::Player player1;
    ariel::Player player2;
    ariel::Player player3;

    ariel::Catan gameManager(player1, player2, player3, true);
    player1.joinGame(&gameManager);
    player2.joinGame(&gameManager);
    player3.joinGame(&gameManager);

    Player *curPlayer = gameManager.chooseStartingPlayer();


    int result = curPlayer->placeSettlement(1, "wood", 1, "brick", 1, "wheat", true);
    CHECK((result == -1)); // not adjacent
}

TEST_CASE("place settlement - not enough resources") {
    cout << "==================== place settlement - not enough resources =====================\n";

    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3, true); // constant board
    catan.chooseStartingPlayer();
    Player *curPlayer = catan.getPlayerTurn();

    // try to place settlement (using resources) without enough resources
    CHECK((curPlayer->placeSettlement(8, BRICK, 10, WHEAT, 9, WOOL, false) == -1));

}


TEST_CASE("place city") {
    cout << "==================== place city =====================\n";
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3, true); // constant board
    catan.chooseStartingPlayer();
    Player *curPlayer = catan.getPlayerTurn();


    //  add 3 iron to the current player
    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(11, IRON));
    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(11, IRON));
    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(11, IRON));

    // add 2 wheat to the current player
    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(10, WHEAT));
    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(10, WHEAT));

    // place settlement to upgrade to city
    CHECK((curPlayer->placeSettlement(2, WHEAT, 5, DESERT, 16, SEA, true) == 0));

    //upgrade to city
    CHECK((curPlayer->placeCity(2, WHEAT, 5, DESERT, 16, SEA, false) == 0));

}

TEST_CASE("place city without resources") {
    cout << "==================== place city without resources =====================\n";
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3, true); // constant board
    catan.chooseStartingPlayer();
    Player *curPlayer = catan.getPlayerTurn();

    // place settlement to upgrade to city
    CHECK((curPlayer->placeSettlement(2, WHEAT, 5, DESERT, 16, SEA, true) == 0));

    // try to place city without resources
    CHECK((curPlayer->placeCity(8, BRICK, 10, WHEAT, 9, WOOL, false) == -1));
}

TEST_CASE("place city- without settlement") {
    cout << "==================== place city without settlement =====================\n";
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3, true); // constant board
    catan.chooseStartingPlayer();
    Player *curPlayer = catan.getPlayerTurn();

    //  add 3 iron to the current player
    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(11, IRON));
    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(11, IRON));
    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(11, IRON));

    // add 2 wheat to the current player
    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(10, WHEAT));
    catan.addResourcesTO(curPlayer, catan.getBoard()->findTile(10, WHEAT));

    // try to place city without settlement first
    CHECK((curPlayer->placeCity(8, BRICK, 10, WHEAT, 9, WOOL, false) == -1));

}

TEST_CASE("placeCity with invalid tiles") {
    cout << "==================== placeCity with invalid tiles =====================\n";

    ariel::Player player1;
    ariel::Player player2;
    ariel::Player player3;

    ariel::Catan gameManager(player1, player2, player3, true);
    player1.joinGame(&gameManager);
    player2.joinGame(&gameManager);
    player3.joinGame(&gameManager);

    Player *curPlayer = gameManager.chooseStartingPlayer();

    int result = curPlayer->placeCity(1, "iron", 1, "wheat", 1, "wool", false);
    CHECK((result == -1)); // no settlement to upgrade
}


TEST_CASE("placeRoad next to UrbanEntity") {
    cout << "==================== placeRoad next to UrbanEntity =====================\n";

    Player player1("a");
    Player player2("b");
    Player player3("c");
    Catan gameManager(player1, player2, player3, true);

    Player *curPlayer = gameManager.chooseStartingPlayer();

    //cur player place a settlement on wheat 10 wheat 11 desert
    CHECK((curPlayer->placeSettlement(10, WHEAT, 11, WHEAT, 5, DESERT, true) == 0));

    int result = curPlayer->placeRoad(10, WHEAT, 5, DESERT);

    CHECK((result == 0));
}

TEST_CASE("placeRoad next to road") {
    cout << "==================== placeRoad next to road =====================\n";

    Player player1("a");
    Player player2("b");
    Player player3("c");
    Catan gameManager(player1, player2, player3, true);

    Player *curPlayer = gameManager.chooseStartingPlayer();

    //cur player place a settlement on wheat 10 wheat 11 desert
    CHECK((curPlayer->placeSettlement(10, WHEAT, 11, WHEAT, 5, DESERT, true) == 0));

    curPlayer->placeRoad(10, WHEAT, 5, DESERT);
    int result = curPlayer->placeRoad(2, WHEAT, 5, DESERT);
    CHECK((result == 0));
}

TEST_CASE("placeRoad with invalid tiles") {
    cout << "==================== placeRoad with invalid tiles =====================\n";

    Player player1("a");
    Player player2("b");
    Player player3("c");
    Catan gameManager(player1, player2, player3, true);

    Player *curPlayer = gameManager.chooseStartingPlayer();


    int result = curPlayer->placeRoad(1, 1, 1, 2);
    CHECK((result == -1)); // location doesn't exist
}

TEST_CASE("placeRoad with not enough resources") {
    cout << "==================== placeRoad with not enough resources =====================\n";

    Player player1("a");
    Player player2("b");
    Player player3("c");
    Catan gameManager(player1, player2, player3, true);

    Player *curPlayer = gameManager.chooseStartingPlayer();

    //cur player place a settlement on wheat 10 wheat 11 desert
    CHECK((curPlayer->placeSettlement(10, WHEAT, 11, WHEAT, 5, DESERT, true) == 0));

    // place two roads to spend the 2 wood and 2 brick we are starting with.
    curPlayer->placeRoad(10, WHEAT, 5, DESERT);
    curPlayer->placeRoad(5, DESERT, 11, WHEAT);

    int result = curPlayer->placeRoad(10, WHEAT, 11, WHEAT);
    CHECK((result == -1));
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

TEST_CASE("buyDevelopmentCard with not enough resources") {
    cout << "==================== buyDevelopmentCard with not enough resources =====================\n";

    ariel::Player player1;
    ariel::Player player2;
    ariel::Player player3;

    ariel::Catan gameManager(player1, player2, player3, true);
    player1.joinGame(&gameManager);
    player2.joinGame(&gameManager);
    player3.joinGame(&gameManager);

    Player *curPlayer = gameManager.chooseStartingPlayer();
    int result = curPlayer->buyDevelopmentCard();
    CHECK((result == -1));
}

TEST_CASE("use your development cards - Knight") {
    cout << "==================== use your development cards - Knight =====================\n";

    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3, true); // constant board
    catan.chooseStartingPlayer();
    Player *curPlayer = catan.getPlayerTurn();

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
}

TEST_CASE("use your development cards - VP") {
    cout << "==================== use your development cards - VP =====================\n";

    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3, true); // constant board
    catan.chooseStartingPlayer();
    Player *curPlayer = catan.getPlayerTurn();

    string cardName = "";
    DevelopmentCard *toUse;
    unsigned int i = 0;
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
        DEBUG("counter " << vpCounter);
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
        int result = catan.getPlayerTurn()->rollDice();
        catan.getPlayerTurn()->endTurn();
        CHECK((result > 0 && result < 13));
    }
    // try to roll not on ur turn
    Player *prevPlayer = catan.getPlayerTurn();
    catan.getPlayerTurn()->endTurn();
    Player *curPlayer = catan.getPlayerTurn();
    CHECK_EQ(prevPlayer->rollDice(), -1);
}

TEST_CASE("roll dice effects") {
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
    int WoolBefore = curPlayer->getResources()[WOOL];
    int WheatBefore = curPlayer->getResources()[WHEAT];

    while (true) {
        result = catan.getPlayerTurn()->rollDice();
        catan.getPlayerTurn()->endTurn();
        if (result == 2) {
            CHECK_EQ(WheatBefore + 1, curPlayer->getResources()[WHEAT]);
            break;
        }
        if (result == 10) {
            CHECK_EQ(WheatBefore + 2, curPlayer->getResources()[WHEAT]);
            break;
        }
        if (result == 8 || result == 9) {
            CHECK_EQ(WoolBefore + 1, curPlayer->getResources()[WOOL]);
            break;
        }
        if (result == 7) {
            WheatBefore = curPlayer->getResources()[WHEAT];
            WoolBefore = curPlayer->getResources()[WOOL];
        }

    }


}

TEST_CASE("get your development cards - none") {
    cout << "==================== get your development cards - none =====================\n";

    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3, true); // constant board
    catan.chooseStartingPlayer();
    Player *curPlayer = catan.getPlayerTurn();

    auto cards = curPlayer->getDevelopmentCards();
    decltype(cards) expect;
    CHECK_EQ(cards, expect);
}

TEST_CASE("rollDice") {
    cout << "==================== roll dice =====================\n";

    ariel::Player player1;
    ariel::Player player2;
    ariel::Player player3;

    ariel::Catan gameManager(player1, player2, player3, true);

    Player *curPlayer = gameManager.chooseStartingPlayer();

    int roll = curPlayer->rollDice();
    CHECK((roll >= 2));
    CHECK((roll <= 12));
}




