//
// Created by alon on 5/20/24.
//

#ifndef CPP_EX3_24_MAIN_CATAN_H
#define CPP_EX3_24_MAIN_CATAN_H
#include "Player.h"
#include "Board.h"


class Catan {
private:
    Board board;
    Player & [] players;
public:
    Catan(Player &p1,Player &p2, Player &p3);
    Board getBoard();
    void printWinner();
    bool checkForWinner();

};


#endif //CPP_EX3_24_MAIN_CATAN_H
