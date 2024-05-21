// 211344015 alonsuissa12@gmail.com
//
// Created by alon on 5/20/24.
//

#include "Resources.hpp"

namespace ariel {

    Road::Road(std::string owner) : ownerName(owner) {}

    void Road::place(Tile &n1, Tile &n2) {
        int edgeSideOfN1 = -1;
        int edgeSideOfN2 = -1;
        for (int i = 0; i < 6; ++i) {
            if (n1.getNeighbor(i).equalTo(n2))
                edgeSideOfN1 = i;
            if (n2.getNeighbor(i).equalTo(n2))
                edgeSideOfN2 = i;
        }
        if (edgeSideOfN1 == -1)
            throw std::invalid_argument("the tiles are not adjacent");
        if (n1.getRoad(edgeSideOfN1) != nullptr)
            throw std::invalid_argument("the place is already taken!");
        bool continues = false;
        Road *pprevn1 = n1.getRoad(((edgeSideOfN1 - 1) % 6));
        Road *ppnextn1 = n1.getRoad((edgeSideOfN1 + 1) % 6);
        ariel::Road *pprevn2 = n2.getRoad((edgeSideOfN1 - 1) % 6);
        ariel::Road *ppnextn2 = n2.getRoad((edgeSideOfN1 + 1) % 6);
        UrbanEntity *urbanEntity1 = n1.getUrbanEntity(edgeSideOfN1);
        UrbanEntity *urbanEntity2 = n1.getUrbanEntity((edgeSideOfN1 + 1) % 6);

        if (pprevn1->getOwnerName() == this->ownerName || pprevn2->getOwnerName() == this->ownerName ||
            ppnextn2->getOwnerName() == this->ownerName || ppnextn1->getOwnerName() == this->ownerName)
            continues = true;
        if (urbanEntity1->getOwner() == ownerName || urbanEntity2->getOwner() == ownerName)
            continues = true;
        if (!continues)
            throw std::invalid_argument(
                    "Invalid location! Roads have to be adjacent to your other roads/cities/settlements");

        n1.placeRoad(this , edgeSideOfN1);
        n2.placeRoad(this, edgeSideOfN2);

        neighborTile1 = &n1;
        neighborTile2 = &n2;

    }


}