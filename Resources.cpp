// 211344015 alonsuissa12@gmail.com
//
// Created by alon on 5/20/24.
//

#include "Resources.hpp"

namespace ariel {

//###################################    FUNCTIONS   ###################################
    //find the edge side from n1 to n2
    int edgeSide(Tile &n1, Tile &n2) {
        int edgeSideOfN1 = -1;
        for (int i = 0; i < 6; ++i) {
            if (n1.getNeighbor(i).equalTo(n2))
                edgeSideOfN1 = i;
        }
        return edgeSideOfN1;
    }


//###################################    ROAD   ###################################

    // constructor
    Road::Road(std::string owner) : ownerName(owner) {}

    //placing the road in the location
    void Road::place(Tile &n1, Tile &n2) {
        int edgeSideOfN1 = edgeSide(n1, n2);
        int edgeSideOfN2 = edgeSide(n2, n1);

        if (edgeSideOfN1 == -1 || edgeSideOfN2 == -1)
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
        if (urbanEntity1->getOwnerName() == this->ownerName || urbanEntity2->getOwnerName() == this->ownerName)
            continues = true;
        if (!continues)
            throw std::invalid_argument(
                    "Invalid location! Roads have to be adjacent to your other roads/cities/settlements");

        n1.placeRoad(this, edgeSideOfN1);
        n2.placeRoad(this, edgeSideOfN2);

        neighborTile1 = &n1;
        neighborTile2 = &n2;

    }


//###################################   URBAN ENTITIES   ###################################

    //constructor
    Settlement::Settlement(Player *owner) {
        this->owner = owner;
        type = SETTLEMENT;
        numOfResources = 1;
        numOfVictoryPoints = 1;
        neighborTileRight = nullptr;
        neighborTileLeft = nullptr;
        neighborTileDown = nullptr;
    }

    // getter for the owner
    Player *UrbanEntity::getOwner() {
        return owner;
    }

    // getter for the owner's name
    std::string UrbanEntity::getOwnerName() {
        return owner->getName();
    }

    // getter for the number of resources this urban entity generates
    int UrbanEntity::getNumOfResources() {
        return numOfResources;
    }

    //getter for the number of resources this urban entity worth
    int UrbanEntity::getNumOfVictoryPoints() {
        return numOfVictoryPoints;
    }

    // getter for the tiles of this urban entity location
    Tile *UrbanEntity::getNeighbor(int num) {
        if (num == RightTile)
            return neighborTileRight;
        if (num == LeftTile)
            return neighborTileLeft;
        if (num == DownTile)
            return neighborTileDown;
        return nullptr;
    }

    //getter for the type of the urban entity
    int UrbanEntity::getType() { return type; }

    //placing the settlement in the location
    void Settlement::place(Tile &n1, Tile &n2, Tile &n3, bool start = false) {
        //find the edges that connect the tiles
        int edgeSideOfN1ToN2 = edgeSide(n1, n2);
        int edgeSideOfN2ToN1 = edgeSide(n2, n1);
        int edgeSideOfN1ToN3 = edgeSide(n1, n3);
        int edgeSideOfN3ToN1 = edgeSide(n3, n1);
        int edgeSideOfN2ToN3 = edgeSide(n2, n3);
        int edgeSideOfN3ToN2 = edgeSide(n3, n2);
        //find the common vertex
        int n1Vertex = -1;
        int n2Vertex = -1;
        int n3Vertex = -1;
        for (int i = 0; i < 6; ++i) { //find n1 vertex
            if ((n1.getNeighbor(i).equalTo(n2) || n1.getNeighbor(i).equalTo(n3)) &&
                n1.getNeighbor((i + 1) % 6).equalTo(n2) || n1.getNeighbor((i + 1) % 6).equalTo(n3))
                n1Vertex = i;
        }
        for (int i = 0; i < 6; ++i) { //find n2 vertex
            if ((n2.getNeighbor(i).equalTo(n1) || n2.getNeighbor(i).equalTo(n3)) &&
                n2.getNeighbor((i + 1) % 6).equalTo(n1) || n2.getNeighbor((i + 1) % 6).equalTo(n3))
                n2Vertex = i;
        }

        for (int i = 0; i < 6; ++i) { //find n3 vertex
            if ((n3.getNeighbor(i).equalTo(n1) || n3.getNeighbor(i).equalTo(n2)) &&
                n3.getNeighbor((i + 1) % 6).equalTo(n1) || n3.getNeighbor((i + 1) % 6).equalTo(n2))
                n3Vertex = i;
        }

        if (edgeSideOfN1ToN2 == -1 || edgeSideOfN1ToN3 == -1 || edgeSideOfN2ToN3 == -1)
            throw std::invalid_argument("the tiles are not adjacent");

        if (n1.getUrbanEntity(n1Vertex) != nullptr)
            throw std::invalid_argument("the place is already taken!");

        if (!start) {
            Road *proadn1n2 = n1.getRoad(edgeSideOfN1ToN2);
            Road *proadn1n3 = n1.getRoad(edgeSideOfN1ToN3);
            Road *proadn2n3 = n2.getRoad(edgeSideOfN2ToN3);


            if (proadn1n2->getOwnerName() != getOwnerName() && proadn1n3->getOwnerName() != getOwnerName() &&
                proadn2n3->getOwnerName() != getOwnerName())
                throw std::invalid_argument("Invalid location! you have to place adjacent to one of your roads");
        }
        if (n1.getUrbanEntity((n1Vertex + 1) % 6) || n1.getUrbanEntity((n1Vertex - 1) % 6) ||
            n2.getUrbanEntity((n2Vertex + 1) % 6) || n2.getUrbanEntity((n2Vertex - 1) % 6) ||
            n3.getUrbanEntity((n3Vertex + 1) % 6) || n3.getUrbanEntity((n3Vertex - 1) % 6))
            throw std::invalid_argument(
                    "Invalid location! you have to place at least 2 edges away from another city/settlement");
        n1.placeUrbanEntity(this, n1Vertex);
        n2.placeUrbanEntity(this, n2Vertex);
        n3.placeUrbanEntity(this, n3Vertex);


    }

    //placing the city in the location
    void City::place(Tile &n1, Tile &n2, Tile &n3, bool start = false) {
        //find the edges that connect the tiles
        int edgeSideOfN1ToN2 = edgeSide(n1, n2);
        int edgeSideOfN2ToN1 = edgeSide(n2, n1);
        int edgeSideOfN1ToN3 = edgeSide(n1, n3);
        int edgeSideOfN3ToN1 = edgeSide(n3, n1);
        int edgeSideOfN2ToN3 = edgeSide(n2, n3);
        int edgeSideOfN3ToN2 = edgeSide(n3, n2);
        //find the common vertex
        int n1Vertex = -1;
        int n2Vertex = -1;
        int n3Vertex = -1;
        for (int i = 0; i < 6; ++i) { //find n1 vertex
            if ((n1.getNeighbor(i).equalTo(n2) || n1.getNeighbor(i).equalTo(n3)) &&
                n1.getNeighbor((i + 1) % 6).equalTo(n2) || n1.getNeighbor((i + 1) % 6).equalTo(n3))
                n1Vertex = i;
        }
        for (int i = 0; i < 6; ++i) { //find n2 vertex
            if ((n2.getNeighbor(i).equalTo(n1) || n2.getNeighbor(i).equalTo(n3)) &&
                n2.getNeighbor((i + 1) % 6).equalTo(n1) || n2.getNeighbor((i + 1) % 6).equalTo(n3))
                n2Vertex = i;
        }
        for (int i = 0; i < 6; ++i) { //find n3 vertex
            if ((n3.getNeighbor(i).equalTo(n1) || n3.getNeighbor(i).equalTo(n2)) &&
                n3.getNeighbor((i + 1) % 6).equalTo(n1) || n3.getNeighbor((i + 1) % 6).equalTo(n2))
                n3Vertex = i;
        }

        if (edgeSideOfN1ToN2 == -1 || edgeSideOfN1ToN3 == -1 || edgeSideOfN2ToN3 == -1)
            throw std::invalid_argument("the tiles are not adjacent");

        if (n1.getUrbanEntity(n1Vertex) == nullptr || n1.getUrbanEntity(n1Vertex)->getOwner() != this->owner ||
            n1.getUrbanEntity(n1Vertex)->getType() == SETTLEMENT)
            throw std::invalid_argument("the location is not containing one of your settlements ");

        n1.placeUrbanEntity(this, n1Vertex);
        n2.placeUrbanEntity(this, n2Vertex);
        n3.placeUrbanEntity(this, n3Vertex);

    }


    //###################################    DEVELOPMENT CARDS    ###################################

    VictoryPoint::VictoryPoint() { this->name = "VictoryPoint"; }

    void VictoryPoint::playCard(Player &p) {
        p.VictoryPoints++;
    }

    Knight::Knight() { name = "Knight"; }

    void Knight::playCard(Player &p) {
        p.numOfKnights++;
        if (p.numOfKnights >= 3)
            p.VictoryPoints += 2;
    }

}