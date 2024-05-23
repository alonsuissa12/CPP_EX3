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

    int convertResourceToInt(std::string resourceTile1) {
        int resNum = -1;
        if (resourceTile1 == "brick" || resourceTile1 == "BRICK")
            resNum = 0;
        if (resourceTile1 == "iron" || resourceTile1 == "IRON")
            resNum = 1;
        if (resourceTile1 == "wheat" || resourceTile1 == "WHEAT")
            resNum = 2;
        if (resourceTile1 == "wood" || resourceTile1 == "WOOD")
            resNum = 3;
        if (resourceTile1 == "wool" || resourceTile1 == "WOOL")
            resNum = 4;
        return resNum;
    }

    std::string convertResourceToString(int resource) {
        if (resource == 0)
            return "brick";
        if (resource == 1)
            return "iron";
        if (resource == 2)
            return "wheat";
        if (resource == 3)
            return "wood";
        if (resource == 4)
            return "wool";
        return "";

    }



//###################################    ROAD   ###################################

    // constructor
    Road::Road(Player *owner) : owner(owner) {}

    //placing the road in the location
    int Road::place(Tile &n1, Tile &n2) {
        int edgeSideOfN1 = edgeSide(n1, n2);
        int edgeSideOfN2 = edgeSide(n2, n1);

        if (edgeSideOfN1 == -1 || edgeSideOfN2 == -1) {
            std::cout << " the tiles r not adjacent!\n";
            return -1;
        }


        if (n1.getRoad(edgeSideOfN1) != nullptr) {
            throw std::invalid_argument("the place is already taken!");
            return -1;
        }

        bool continues = false;
        Road *pprevn1 = n1.getRoad(((edgeSideOfN1 - 1) % 6));
        Road *ppnextn1 = n1.getRoad((edgeSideOfN1 + 1) % 6);
        ariel::Road *pprevn2 = n2.getRoad((edgeSideOfN1 - 1) % 6);
        ariel::Road *ppnextn2 = n2.getRoad((edgeSideOfN1 + 1) % 6);
        UrbanEntity *urbanEntity1 = n1.getUrbanEntity(edgeSideOfN1);
        UrbanEntity *urbanEntity2 = n1.getUrbanEntity((edgeSideOfN1 + 1) % 6);

        if (pprevn1->owner == this->owner || pprevn2->owner == this->owner ||
            ppnextn2->owner == this->owner || ppnextn1->owner == this->owner)
            continues = true;
        if (urbanEntity1->getOwner() == this->owner || urbanEntity2->getOwner() == this->owner)
            continues = true;
        if (!continues) {
            std::cout << "Invalid location! Roads have to be adjacent to your other roads/cities/settlements\n";
            return -1;
        }

        n1.placeRoad(this, edgeSideOfN1);
        n2.placeRoad(this, edgeSideOfN2);

        neighborTile1 = &n1;
        neighborTile2 = &n2;
        return 0;
    }

    std::string Road::getOwnerName() {
        return owner->getName();
    }

    Player *Road::getOwner() {
        return owner;
    }

//###################################   URBAN ENTITIES   ###################################

    UrbanEntity::~UrbanEntity() {}

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
    int Settlement::place(Tile &n1, Tile &n2, Tile &n3, bool start = false) {
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

        if (edgeSideOfN1ToN2 == -1 || edgeSideOfN1ToN3 == -1 || edgeSideOfN2ToN3 == -1) {
            std::cout << "the tiles are not adjacent\n";
            return -1;
        }

        if (n1.getUrbanEntity(n1Vertex) != nullptr) {
            std::cout << "the place is already taken!\n";
            return -1;
        }
        if (!start) {
            Road *proadn1n2 = n1.getRoad(edgeSideOfN1ToN2);
            Road *proadn1n3 = n1.getRoad(edgeSideOfN1ToN3);
            Road *proadn2n3 = n2.getRoad(edgeSideOfN2ToN3);


            if (proadn1n2->getOwnerName() != getOwnerName() && proadn1n3->getOwnerName() != getOwnerName() &&
                proadn2n3->getOwnerName() != getOwnerName()) {
                std::cout << "Invalid location! you have to place adjacent to one of your roads\n";
                return -1;
            }
        }
        if (n1.getUrbanEntity((n1Vertex + 1) % 6) || n1.getUrbanEntity((n1Vertex - 1) % 6) ||
            n2.getUrbanEntity((n2Vertex + 1) % 6) || n2.getUrbanEntity((n2Vertex - 1) % 6) ||
            n3.getUrbanEntity((n3Vertex + 1) % 6) || n3.getUrbanEntity((n3Vertex - 1) % 6)) {
            std::cout << "Invalid location! you have to place at least 2 edges away from another city/settlement\n";
            return -1;
        }

        int ans1 = n1.placeUrbanEntity(this, n1Vertex);
        int ans2 = n2.placeUrbanEntity(this, n2Vertex);
        int ans3 = n3.placeUrbanEntity(this, n3Vertex);
        if (ans1 == -1 || ans2 == -1 || ans3 == -1) {
            std::cout << "Invalid location! \n";
            return -1;
        }
        return 0;

    }

//constructor
    City::City(Player *p) {
        this->owner = owner;
        type = CITY;
        numOfResources = 2;
        numOfVictoryPoints = 2;
        neighborTileRight = nullptr;
        neighborTileLeft = nullptr;
        neighborTileDown = nullptr;
    }

//placing the city in the location
    int City::place(Tile &n1, Tile &n2, Tile &n3, bool start = false) {
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

        if (edgeSideOfN1ToN2 == -1 || edgeSideOfN1ToN3 == -1 || edgeSideOfN2ToN3 == -1) {
            std::cout << "the tiles are not adjacent\n";
            return -1;
        }

        if (n1.getUrbanEntity(n1Vertex) == nullptr || n1.getUrbanEntity(n1Vertex)->getOwner() != this->owner ||
            n1.getUrbanEntity(n1Vertex)->getType() == SETTLEMENT) {
            std::cout << "the location is not containing one of your settlements\n";
            return -1;
        }


        int ans1 = n1.placeUrbanEntity(this, n1Vertex);
        int ans2 = n2.placeUrbanEntity(this, n2Vertex);
        int ans3 = n3.placeUrbanEntity(this, n3Vertex);
        if (ans1 == -1 || ans2 == -1 || ans3 == -1) {
            std::cout << "Invalid location! \n";
            return -1;
        }
        return 0;

    }


//###################################    DEVELOPMENT CARDS    ###################################

    DevelopmentCard::~DevelopmentCard() {}

    std::string DevelopmentCard::getName() {
        return name;
    }

    VictoryPoint::VictoryPoint(Catan *gm) {
        this->name = "VictoryPoint";
        gameManager = gm;
    }

    void VictoryPoint::playCard(Player &p) {
        p.VictoryPoints++;
        std::cout << p.name << " played a victory point card and now have " << p.VictoryPoints << " points!\n";
    }

    Knight::Knight(Catan *gm) {
        name = "Knight";
        gameManager = gm;
    }

    void Knight::playCard(Player &p) {
        p.numOfKnights++;
        if (p.numOfKnights >= 3)
            p.VictoryPoints += 2;
    }

    Monopole::Monopole(Catan *gm) {
        name = "Monopole";
        gameManager = gm;
    }

    void Monopole::playCard(Player &p) {
        int resource = -1;
        std::cout << "choose a resource for monopoly card(type a number):\n";
        while (resource < 0 || resource > 4) {
            std::cout << "BRICK: 0, IRON: 1, WHEAT: 2, WOOD: 3, WOOL: 4\n";
            std::cin >> resource;
        }
        this->gameManager->monopole(&p, resource);
    }

    RoadsBuild::RoadsBuild(Catan *catan) {
        name = "RoadsBuild";
        gameManager = catan;
    }

    void RoadsBuild::playCard(Player &p) {
        std::cout << " played roads build\n";

        int roadsLeft = p.unusedRoads.size();
        int roadsToGet = 0;
        if (roadsLeft >= 2)
            roadsToGet = 2;
        else if (roadsLeft == 1)
            roadsToGet = 1;

        while (roadsToGet > 0) {
            int resource1 = -1;
            int tileNumber1 = -1;
            int resource2 = -1;
            int tileNumber2 = -1;
            bool validTile1 = false;
            bool validTile2 = false;

            std::cout << " choose where u want to place your road:\n";
            std::cout << " (choose two tiles and the road will build between them)\n";


            std::cout << "Choose where you want to place your road:\n"
                      << "(choose two tiles and the road will be built between them)\n";

            while (!validTile1) {
                std::cout << "Tile 1:\n";
                std::cout
                        << "----Enter the resource of the tile (0 for brick, 1 for iron, 2 for wheat, 3 for wood, 4 for wool):\n";
                std::cin >> resource1;

                std::cout << "----Enter the dice number of the tile:\n";
                std::cin >> tileNumber1;

                validTile1 = (resource1 >= 0 && resource1 <= 4) &&
                             (tileNumber1 >= 2 && tileNumber1 <= 12) &&
                             (gameManager->findTile(tileNumber1, resource1) != nullptr);

                if (!validTile1) {
                    std::cout << "Invalid tile. Please try again.\n";
                    std::cin.clear(); // Clear error flags
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                }
            }
            // tile 2

            std::cout << "Choose where you want to place your road:\n"
                      << "(choose two tiles and the road will be built between them)\n";

            while (!validTile2) {
                std::cout << "Tile 2:\n";
                std::cout
                        << "----Enter the resource of the tile (0 for brick, 1 for iron, 2 for wheat, 3 for wood, 4 for wool):\n";
                std::cin >> resource2;

                std::cout << "----Enter the dice number of the tile:\n";
                std::cin >> tileNumber2;

                validTile2 = (resource2 >= 0 && resource2 <= 4) &&
                             (tileNumber2 >= 2 && tileNumber2 <= 12) &&
                             (gameManager->findTile(tileNumber2, resource2) != nullptr);

                if (!validTile2) {
                    std::cout << "Invalid tile. Please try again.\n";
                    std::cin.clear(); // Clear error flags
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                }
            }

            p.resources[BRICK]++;
            p.resources[WOOD]++;
            int placed = p.placeRoad(tileNumber1, resource1, tileNumber2, resource2);
            if (placed == 0) {
                roadsToGet--;
                std::cout << " first road build successfully\n";
            } else {
                std::cout << " there was a problem with building this road, pleas try again\n";
                p.resources[BRICK]--;
                p.resources[WOOD]--;
                resource1 = -1;
                tileNumber1 = -1;
                resource2 = -1;
                tileNumber2 = -1;
                validTile1 = false;
                validTile2 = false;
            }
        }
    }

    YearOfPlenty::YearOfPlenty(Catan *gm) {
        name = "YearOfPlenty";
        gameManager = gm;
    }

    void YearOfPlenty::playCard(Player &p) {
        int resource = -1;
        while (resource < 0 || resource > 4 || std::cin.fail()) {
            std::cout << "Choose your first resource: BRICK: 0, IRON: 1, WHEAT: 2, WOOD: 3, WOOL: 4\n";
            std::cin.clear(); // Clear any error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
            std::cin >> resource;
        }
        p.resources[resource++];
        resource = -1;
        while (resource < 0 || resource > 4 || std::cin.fail()) {
            std::cout << "Choose your second resource: BRICK: 0, IRON: 1, WHEAT: 2, WOOD: 3, WOOL: 4\n";
            std::cin.clear(); // Clear any error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
            std::cin >> resource;
        }
        p.resources[resource++];
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

    int Tile::placeUrbanEntity(UrbanEntity *UrbanEntity, int side) {
        if (side > 5 || side < 0) {
            std::cout << "side should be between 0 to 5 (include 0 and 5)\n";
            return -1;
        }
        urbanEntities[side] = UrbanEntity;
        return 0;
    }

    int Tile::placeRoad(Road *road, int side) {
        if (side > 5 || side < 0) {
            std::cout << "side should be between 0 to 5 (include 0 and 5)\n";
            return -1;
        }
        roads[side] = road;
        return 0;
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

    int Tile::getResource() {
        return convertResourceToInt(resource);
    }


    bool operator==(const Tile &t1, const Tile &t2) {
        return (&t1 == &t2);
    }

    bool operator!=(const Tile &t1, const Tile &t2) {
        return &t1 != &t2;
    }

    int Tile::getNumber() {
        return number;
    }

    std::ostream &operator<<(std::ostream &os, const Tile &tile) {
        if (tile.isSea)
            os << "sea";
        else if (tile.isDesert)
            os << "desert";
        else {
            os << tile.resource << " " << std::to_string(tile.number);
        }
        return os;
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
            Tile *tile = new Tile(numbers[i], "iron");
            tiles.push_back(tile);
        }

        // 4 wood tiles
        for (unsigned int i = 0; i < 4; ++i) {
            Tile *tile = new Tile(numbers[i + 3], "wood");
            tiles.push_back(tile);
        }
        // 4 wool tiles
        for (unsigned int i = 0; i < 4; ++i) {
            Tile *tile = new Tile(numbers[i + 7], "wool");
            tiles.push_back(tile);
        }
        // 3 brick tiles
        for (unsigned int i = 0; i < 3; ++i) {
            Tile *tile = new Tile(numbers[i + 11], "brick");
            tiles.push_back(tile);
        }

        // 4 wheat tiles
        for (unsigned int i = 0; i < 4; ++i) {
            Tile *tile = new Tile(numbers[i + 14], "wheat");
            tiles.push_back(tile);
        }

        // desert tile
        Tile *desert = new Tile(0, "nothing", false, true);
        tiles.push_back(desert);
        //shuffle the tiles
        std::shuffle(tiles.begin(), tiles.end(), std::default_random_engine((unsigned long) std::time(nullptr)));

        // 18 sea tiles
        unsigned int locationsForSea[18] = {0, 1, 2, 3, 4, 8, 9, 14, 15, 21, 22, 27,
                                            28, 32, 33, 34, 35, 36};
        unsigned int shift = 0;

        for (unsigned int i = 0; i < 18; ++i) {
            Tile *tile = new Tile(0, "nothing", true, false);
            tiles.insert(tiles.begin() + locationsForSea[i], tile);
            shift++;

        }

        //update neighbors

        unsigned int rowSize[] = {4, 5, 6, 7, 6, 5, 4};
        int rowSizeLength = 7;
        shift = 0;
        unsigned int secondHalPlus = 0;
        unsigned int firstHalfPlus = 1;


        for (unsigned int i = 0; i < rowSizeLength; ++i) {
            if (i != 0)
                shift += rowSize[i - 1];
            if (i == 3) {
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
                if (i != 0 && (j + 1 == rowSize[i] && i >= 4))
                    tiles[j + shift]->UpdateNeighbor(*tiles[shift + j - rowSize[i] + firstHalfPlus], UpRightEdge);

                if (i + 1 != rowSizeLength && (i < 4 || j + 1 != rowSize[i]))
                    tiles[j + shift]->UpdateNeighbor(*tiles[shift + j + rowSize[i] + firstHalfPlus], DownRightEdge);
                if (i + 1 != rowSizeLength && (i < 4 || j != 0))
                    tiles[j + shift]->UpdateNeighbor(*tiles[shift + j + rowSize[i] + secondHalPlus], DownLeftEdge);

            }
        }


    }

    Board::~Board() {
        // Deallocate memory for each tile
        for (Tile *tile: tiles) {
            delete tile;
        }
        // Clear the vector of tiles
        tiles.clear();
    }

    void Board::printBoard() {
        unsigned int first = 4;
        unsigned int second = 5;
        unsigned int third = 6;
        unsigned int fourth = 7;
        unsigned int fifth = 6;
        unsigned int sixth = 5;
        unsigned int seventh = 4;
        std::cout << "\n              ************ CATAN BOARD ************\n";
        std::cout << "                       ";
        for (unsigned int i = 0; i < first; ++i) { // first row
            std::cout << *tiles[i] << "  ";
        }
        std::cout << "\n               ";
        for (unsigned int i = first; i < first + second; ++i) { //second row
            std::cout << *tiles[i] << "  ";
        }
        std::cout << "\n           ";
        for (unsigned int i = first + second; i < first + second + third; ++i) { //third row
            std::cout << *tiles[i] << "  ";
        }
        std::cout << "\n      ";
        for (unsigned int i = first + second + third; i < first + second + third + fourth; ++i) { //fourth row
            std::cout << *tiles[i] << "  ";
        }
        std::cout << "\n           ";
        for (unsigned int i = first + second + third + fourth;
             i < first + second + third + fourth + fifth; ++i) { //fifth row
            std::cout << *tiles[i] << "  ";
        }
        std::cout << "\n               ";
        for (unsigned int i = first + second + third + fourth + fifth;
             i < first + second + third + fourth + fifth + sixth; ++i) { //sixth row
            std::cout << *tiles[i] << "  ";
        }
        std::cout << "\n                       ";
        for (unsigned int i = first + second + third + fourth + fifth + sixth;
             i < first + second + third + fourth + fifth + sixth + seventh; ++i) { //seventh row
            std::cout << *tiles[i] << "  ";
        }
        std::cout << "\n             **************************************\n\n";
    }

    Tile *Board::findTile(int numTile, int resourceTile) {
        for (Tile *t: tiles)
            if (t->getResource() == resourceTile && t->getNumber() == numTile)
                return t;
        return nullptr;
    }


}