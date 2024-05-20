// 211344015 alonsuissa12@gmail.com
// Created by alon on 5/20/24.
//

#ifndef CPP_EX3_24_MAIN_CATAN_H
#define CPP_EX3_24_MAIN_CATAN_H
#include "Player.hpp"
#include "Board.hpp"
#include "Resources.hpp"
#include <vector>

namespace ariel {

    class Catan {
    private:
        Board board;
        std::vector <Player> players;
        DevelopmentCardsDeck developmentCardsDeck;
    public:
        Catan(Player &p1, Player &p2, Player &p3);

        Board getBoard();

        void printWinner();

        bool checkForWinner();

        DevelopmentCard *drawDevelopmentCard();

        Player &ChooseStartingPlayer();

    };

}
#endif //CPP_EX3_24_MAIN_CATAN_H
