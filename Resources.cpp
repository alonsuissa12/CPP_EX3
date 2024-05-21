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
            if (n1.getNeighbor(i) == n2)
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
            void UpdateNeighbor(Tile &neighbor);
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
            if ((n1.getNeighbor(i) == n3 || n1.getNeighbor(i) == n2) &&
                (n1.getNeighbor((i + 1) % 6) == n3 || n1.getNeighbor((i + 1) % 6) == n2))
                n1Vertex = i;
        }
        for (int i = 0; i < 6; ++i) { //find n2 vertex
            if ((n2.getNeighbor(i) == n1 || n2.getNeighbor(i) == n3) &&
                (n2.getNeighbor((i + 1) % 6) == n1 || n2.getNeighbor((i + 1) % 6) == n3))
                n2Vertex = i;
        }
        for (int i = 0; i < 6; ++i) { //find n3 vertex
            if ((n3.getNeighbor(i) == n1 || n3.getNeighbor(i) == n2) &&
                (n3.getNeighbor((i + 1) % 6) == n1 || n3.getNeighbor((i + 1) % 6) == n2))
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
            if ((n1.getNeighbor(i) == n3 || n1.getNeighbor(i) == n2) &&
                (n1.getNeighbor((i + 1) % 6) == n3 || n1.getNeighbor((i + 1) % 6) == n2))
                n1Vertex = i;
        }
        for (int i = 0; i < 6; ++i) { //find n2 vertex
            if ((n2.getNeighbor(i) == n1 || n2.getNeighbor(i) == n3) &&
                (n2.getNeighbor((i + 1) % 6) == n1 || n2.getNeighbor((i + 1) % 6) == n3))
                n2Vertex = i;
        }
        for (int i = 0; i < 6; ++i) { //find n3 vertex
            if ((n3.getNeighbor(i) == n1 || n3.getNeighbor(i) == n2) &&
                (n3.getNeighbor((i + 1) % 6) == n1 || n3.getNeighbor((i + 1) % 6) == n2))
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

    Monopole::Monopole() { name = "Monopole"; }

    void Monopole::playCard(Player &p) {
        // todo: implement
    }

    YearOfPlenty::YearOfPlenty() { name = "YearOfPlenty"; }

    void YearOfPlenty::playCard(Player &p) {
        //todo: implement
    }

    //###################################   TILE   ###################################

    Tile::Tile(int dieNum, std::string resource, bool issea = false, bool isDesert = false) {
        isSea = issea;
        this->isDesert = isDesert;
        this->resource = resource;
        number = dieNum;
    };

    void Tile::UpdateNeighbor(Tile &neighbor, int side) {
        if (side > 5 || side < 0)
            throw std::invalid_argument("side should be between 0 to 5 (include 0 and 5)");
        neighbors[side] = &neighbor;
    }

    void Tile::placeUrbanEntity(UrbanEntity *UrbanEntity, int side) {
        if (side > 5 || side < 0)
            throw std::invalid_argument("side should be between 0 to 5 (include 0 and 5)");
        urbanEntities[side] = UrbanEntity;
    }

    void Tile::placeRoad(Road *road, int side) {
        if (side > 5 || side < 0)
            throw std::invalid_argument("side should be between 0 to 5 (include 0 and 5)");
        roads[side] = road;
    }

    Tile &Tile::getNeighbor(int side) {
        if (side > 5 || side < 0)
            throw std::invalid_argument("side should be between 0 to 5 (include 0 and 5)");
        return *neighbors[side];
    }

    Road *Tile::getRoad(int side) {
        if (side > 5 || side < 0)
            throw std::invalid_argument("side should be between 0 to 5 (include 0 and 5)");
        return roads[side];
    }

    UrbanEntity *Tile::getUrbanEntity(int side) {
        if (side > 5 || side < 0)
            throw std::invalid_argument("side should be between 0 to 5 (include 0 and 5)");
        return urbanEntities[side];
    }

    bool operator==(const Tile &t1, const Tile &t2) {
        return (&t1 == &t2);
    }

    bool operator!=(const Tile &t1, const Tile &t2) {
        return !(t1 == t2);
    }

    //###################################   BOARD   ###################################
    Board::Board() {
        // Seed the random number generator
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        // numbers for the tiles
        std::vector<int> numbers = {2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12};

        // Shuffle the vector
        std::shuffle(numbers.begin(), numbers.end(), std::default_random_engine((unsigned long) std::time(nullptr)));

        // 18 yielding tiles:
        // 3 iron tiles
        for (unsigned int i = 0; i < 3; ++i) {
            Tile tile = Tile(numbers[i], "iron");
            tiles.push_back(&tile);
        }
        // 4 wood tiles
        for (unsigned int i = 0; i < 4; ++i) {
            Tile tile = Tile(numbers[i + 3], "wood");
            tiles.push_back(&tile);
        }
        // 4 wool tiles
        for (unsigned int i = 0; i < 4; ++i) {
            Tile tile = Tile(numbers[i + 7], "wool");
            tiles.push_back(&tile);
        }
        // 3 brick tiles
        for (unsigned int i = 0; i < 3; ++i) {
            Tile tile = Tile(numbers[i + 11], "brick");
            tiles.push_back(&tile);
        }
        // 4 wheat tiles
        for (unsigned int i = 0; i < 4; ++i) {
            Tile tile = Tile(numbers[i + 14], "wheat");
            tiles.push_back(&tile);
        }

        // desert tile
        Tile desert = Tile(0, "nothing", false, true);
        tiles.push_back(&desert);

        //shuffle the tiles
        std::shuffle(tiles.begin(), tiles.end(), std::default_random_engine((unsigned long) std::time(nullptr)));

        // 18 sea tiles
        unsigned int locationsForSea[18] = {0, 1, 2, 3, 4, 8, 9, 14, 15, 21, 22, 27,
                                            28, 32, 33, 34, 35, 36};
        unsigned int shift = 0;
        for (unsigned int i = 0; i < 18; ++i) {
            Tile tile = Tile(0, "nothing", true, false);
            tiles.insert(tiles.begin() + locationsForSea[i + shift], &tile);
            shift++;
        }

        //update neighbors

        unsigned int rowSize[] = {4, 5, 6, 7, 6, 5, 4};
        int rowSizeLength = 7;
        shift = 0;
        unsigned int secondHalPlus = 0;
        unsigned int firstHalfPlus = 1;


        for (unsigned int i = 0; i < rowSizeLength; ++i) {
            shift += rowSize[i];
            if(i == 3) {
                secondHalPlus = 1;
                firstHalfPlus = 0;
            }
            for (unsigned int j = 0; j < rowSize[i]; ++j) {
                if (j != 0)
                    tiles[j + shift]->UpdateNeighbor(*tiles[shift + j - 1], LeftEdge);
                if (j != rowSize[i] - 1)
                    tiles[j + shift]->UpdateNeighbor(*tiles[shift + j + 1], RightEdge);
                if (i != 0 && (j != 0 && i >= 4))
                    tiles[j + shift]->UpdateNeighbor(*tiles[shift + j - rowSize[i] - secondHalPlus], UpLeftEdge);
                if (i != 0 &&  (j+1 == rowSize[i] && i >= 4))
                    tiles[j + shift]->UpdateNeighbor(*tiles[shift + j - rowSize[i] + firstHalfPlus], UpRightEdge);


                if (i+1 != rowSizeLength && (i<4 || j+1 != rowSize[i] ))
                    tiles[j + shift]->UpdateNeighbor(*tiles[shift + j + rowSize[i]+firstHalfPlus], DownRightEdge);
                if ( i+1 != rowSizeLength && (i<4 || j != 0))
                    tiles[j + shift]->UpdateNeighbor(*tiles[shift + j + rowSize[i] + secondHalPlus], DownLeftEdge);

            }
        }


    }

    void Board::printBoard(){
        std::cout << "print board (need to implement)" << std::endl;
        // todo: implement printBoard (maybe)
    }


}