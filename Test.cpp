// 211344015 alonsuissa12@gmail.com
// Created by alon on 5/28/24.
//
// todo: tests!
#include "doctest.h"
#include "Resources.hpp"

using namespace ariel;
using namespace std;
using namespace doctest;


TEST_CASE("place settlement/road"){
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3, true); // constant board
    catan.chooseStartingPlayer();
    Player * curPlayer = catan.getPlayerTurn();

    // try to place settlement (using resources) without enough resources
    CHECK((curPlayer->placeSettlement(8, 0,10,2,9,4,  false) ==-1));

    // p1 placing on iron 11, iron 1,wood 4 and road on iron 3 wood 4
    CHECK((curPlayer->placeSettlement(11,1,3,1,4,3, true)==0));

    //p1 place a settlement on wool 6 brick 9 brick 10
    CHECK((curPlayer->placeSettlement(6, 4,9,0,10,0, true)==0));

    //p1 place a settlement on wheat 10 wheat 11 desert
    CHECK((curPlayer->placeSettlement(10, 2,11,2,5,5, true)==0));

    catan.addResourcesTO(curPlayer,catan.getBoard()->findTile(10,0));  // add brick to p1
    catan.addResourcesTO(curPlayer,catan.getBoard()->findTile(10,0));  // add brick to p1
    catan.addResourcesTO(curPlayer,catan.getBoard()->findTile(10,0));  // add brick to p1

    catan.addResourcesTO(curPlayer,catan.getBoard()->findTile(11,1));  // add iron to p1

    catan.addResourcesTO(curPlayer,catan.getBoard()->findTile(10,2));  // add wheat to p1

    catan.addResourcesTO(curPlayer,catan.getBoard()->findTile(4,3));  // add wood to p1
    catan.addResourcesTO(curPlayer,catan.getBoard()->findTile(4,3));  // add wood to p1
    catan.addResourcesTO(curPlayer,catan.getBoard()->findTile(4,3));  // add wood to p1

    catan.addResourcesTO(curPlayer,catan.getBoard()->findTile(6,4));  // add wool to p1


    //try to place on taken spot
    CHECK((curPlayer->placeSettlement(10, 2,11,2,5,5, false) ==-1));

    //try to place only one edge away from another settlement
    CHECK((curPlayer->placeSettlement(13, 6,11,2,5,5, false) ==-1));

    // placing a settlement not on the start of the game without roads (not continues)
    CHECK((curPlayer->placeSettlement(10,2,2,2,5,5, false)==-1));

    cout<< "-----------\n";
    // try to place settlement not on the start of the game in a good way
    curPlayer->placeRoad(10, 2,5,5);
    curPlayer->placeRoad(5,5,2,2);
    CHECK((curPlayer->placeSettlement(2,2,5,5,16,6, false)==0));

}
//
//TEST_CASE(){}
//
//TEST_CASE(){}
//
//TEST_CASE(){}
//
//TEST_CASE(){}
//
//TEST_CASE(){}
//
//TEST_CASE(){}
//
//TEST_CASE(){}

