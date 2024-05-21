// 211344015 alonsuissa12@gmail.com
//
// Created by alon on 5/20/24.
//
#include "Player.hpp"

namespace ariel{

    bool operator==(const Player& p1, const Player & p2){
        return (&p1 == &p2);
    }
    bool operator!=(const Player& p1, const Player & p2){
        return !(p1 == p2);
    }


}
