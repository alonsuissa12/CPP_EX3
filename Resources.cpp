// 211344015 alonsuissa12@gmail.com
//
// Created by alon on 5/20/24.
//

#include "Resources.hpp"

namespace ariel {

//###################################    FUNCTIONS   ###################################
    // Finds the edge side from tile n1 to tile n2.
    // Parameters:
    // - n1: Reference to the first tile.
    // - n2: Reference to the second tile.
    // Returns:
    // - The index of the edge side of tile n1 that connects to tile n2, or -1 if not found.
    int edgeSide(Tile &n1, Tile &n2);

    int edgeSide(Tile &n1, Tile &n2) {
        int edgeSideOfN1 = -1;
        for (int i = 0; i < 6; ++i) {
            if (*n1.getNeighbor(i) == n2)
                edgeSideOfN1 = i;
        }
        return edgeSideOfN1;
    }

    // Converts a resource name string to its corresponding integer representation.
    // Parameters:
    // - resourceTile1: The resource name string to be converted.
    // Returns:
    // - The integer representation of the resource: 0 for brick, 1 for iron, 2 for wheat, 3 for wood, 4 for wool, 5 for desert, 6 for sea.
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
        if (resourceTile1 == "desert" || resourceTile1 == "DESERT")
            resNum = 5;
        if (resourceTile1 == "sea" || resourceTile1 == "SEA")
            resNum = 6;
        return resNum;
    }

    // Converts an integer representation of a resource to its corresponding string representation.
    // Parameters:
    // - resource: The integer representation of the resource.
    // Returns:
    // - The string representation of the resource.
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

    // Constructor for Road class
    // Parameters:
    // - owner: Pointer to the player who owns this road
    Road::Road(Player *owner) : owner(owner) {}

    // Function to place the road between two tiles
    // Parameters:
    // - n1: First tile
    // - n2: Second tile
    // Returns:
    // - 0 if road is successfully placed, -1 otherwise
    int Road::place(Tile &n1, Tile &n2) {
        int edgeSideOfN1 = edgeSide(n1, n2);
        int edgeSideOfN2 = edgeSide(n2, n1);

        if (edgeSideOfN1 == -1 || edgeSideOfN2 == -1) {
            std::cout << " the tiles r not adjacent!\n";
            return -1;
        }

        if (n1.getRoad(edgeSideOfN1) != nullptr) {
            std:: cout << "the place is already taken!" << std::endl;
            return -1;
        }

        //  check continues
        bool continues = false;
        // check the two adjacent roads
        Road *pprevn1 = n1.getRoad(((edgeSideOfN1 - 1 + 6) % 6));
        Road *ppnextn1 = n1.getRoad((edgeSideOfN1 + 1) % 6);
        Road *pprevn2 = n2.getRoad((edgeSideOfN2 - 1 + 6) % 6);
        Road *ppnextn2 = n2.getRoad((edgeSideOfN2 + 1) % 6);


        // check the adjacent urban entities
        UrbanEntity *urbanEntity1 = n1.getUrbanEntity(edgeSideOfN1);
        UrbanEntity *urbanEntity2 = n1.getUrbanEntity((edgeSideOfN1 + 1) % 6);

        // if one of the adjacent roads belongs to this player
        if ((pprevn1 != nullptr && pprevn1->owner == this->owner) ||
            (pprevn2 != nullptr && pprevn2->owner == this->owner) ||
            (ppnextn2 != nullptr && ppnextn2->owner == this->owner) ||
            (ppnextn1 != nullptr && ppnextn1->owner == this->owner))
            continues = true;

        // if one of the adjacent urban entities belongs to this player
        if ((urbanEntity1 != nullptr && urbanEntity1->getOwner() == this->owner) ||
            (urbanEntity2 != nullptr && urbanEntity2->getOwner() == this->owner))
            continues = true;
        if (!continues) {
            std::cout << "Invalid location! Roads have to be adjacent to your other roads/cities/settlements\n";
            return -1;
        }

        int ans1 = n1.placeRoad(this, edgeSideOfN1);
        int ans2 = n2.placeRoad(this, edgeSideOfN2);
        if (ans1 == -1 || ans2 == -1)
            return -1;

        // update neighbors of road
        neighborTile1 = &n1;
        neighborTile2 = &n2;

        return 0;
    }

    // Function to get the owner's name of the road
    std::string Road::getOwnerName() {
        return owner->getName();
    }

    // Function to get the owner of the road
    Player *Road::getOwner() {
        return owner;
    }

    Tile *Road::getNeighbor(int side) {
        if (side == 0)
            return neighborTile1;
        if (side == 1)
            return neighborTile2;
        return nullptr;
    }

//###################################   URBAN ENTITIES   ###################################


    // Destructor for UrbanEntity
    UrbanEntity::~UrbanEntity() {}

    // Getter for the owner of the UrbanEntity
    // Returns:
    // - Pointer to the owner Player
    Player *UrbanEntity::getOwner() {
        return owner;
    }

    // Getter for the name of the owner of the UrbanEntity
    // Returns:
    // - Name of the owner Player
    std::string UrbanEntity::getOwnerName() {
        return owner->getName();
    }

    // Getter for the number of resources this urban entity generates
    // Returns:
    // - Number of resources generated by the urban entity
    int UrbanEntity::getNumOfResources() {
        return numOfResources;
    }

    // Getter for the number of victory points this urban entity is worth
    // Returns:
    // - Number of victory points the urban entity is worth
    int UrbanEntity::getNumOfVictoryPoints() {
        return numOfVictoryPoints;
    }

    // Getter for the neighboring Tile of this urban entity
    // Parameters:
    // - num: Number indicating the direction of the neighbor (Right, Left, Down)
    // Returns:
    // - Pointer to the neighboring Tile in the specified direction
    Tile *UrbanEntity::getNeighbor(int num) {
        if (num == RightTile)
            return neighborTileRight;
        if (num == LeftTile)
            return neighborTileLeft;
        if (num == DownTile)
            return neighborTileDown;
        return nullptr;
    }

    // Getter for the type of the urban entity
    // Returns:
    // - Type of the urban entity (SETTLEMENT or CITY)
    int UrbanEntity::getType() {
        return type;
    }

    // Constructor for Settlement
    // Parameters:
    // - owner: Pointer to the owner of the settlement
    Settlement::Settlement(Player *owner) {
        this->owner = owner;
        type = SETTLEMENT;
        numOfResources = 1;
        numOfVictoryPoints = 1;
        neighborTileRight = nullptr;
        neighborTileLeft = nullptr;
        neighborTileDown = nullptr;
    }


    // Function to place a Settlement on the board
    // Parameters:
    // - n1: First Tile
    // - n2: Second Tile
    // - n3: Third Tile
    // - start: Flag indicating if it's the start of the game (default: false)
    // Returns:
    // - 0 if the Settlement is successfully placed, -1 otherwise
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
            int k = (i - 1 + 6) % 6;
            if (n1.getNeighbor(i) != nullptr || n1.getNeighbor(k) != nullptr)
                if ((*n1.getNeighbor(i) == n3 || *n1.getNeighbor(i) == n2) &&
                    (*n1.getNeighbor(k) == n3 || *n1.getNeighbor(k) == n2))
                    n1Vertex = i;
        }
        for (int i = 0; i < 6; ++i) { //find n2 vertex
            int k = (i - 1 + 6) % 6;
            if (n2.getNeighbor(i) != nullptr || n2.getNeighbor(k) != nullptr)
                if ((*n2.getNeighbor(i) == n1 || *n2.getNeighbor(i) == n3) &&
                    (*n2.getNeighbor(k) == n1 || *n2.getNeighbor(k) == n3))
                    n2Vertex = i;
        }
        for (int i = 0; i < 6; ++i) { //find n3 vertex
            int k = (i - 1 + 6) % 6;
            if (n3.getNeighbor(i) != nullptr || n3.getNeighbor(k) != nullptr)
                if ((*n3.getNeighbor(i) == n1 || *n3.getNeighbor(i) == n2) &&
                    (*n3.getNeighbor(k) == n1 || *n3.getNeighbor(k) == n2))
                    n3Vertex = i;

        }

        if (n1Vertex == -1 || n2Vertex == -1 || n3Vertex == -1) {
            std::cout << "the tiles are not adjacent(1)\n";
            return -1;
        }


        if (edgeSideOfN1ToN2 == -1 || edgeSideOfN1ToN3 == -1 || edgeSideOfN2ToN3 == -1) {
            std::cout << edgeSideOfN1ToN2 << ", " << edgeSideOfN1ToN3 << " , " << edgeSideOfN2ToN3 << " \n";
            std::cout << "the tiles are not adjacent(2)\n";
            return -1;
        }

        if (n1.getUrbanEntity(n1Vertex) != nullptr) {
            std::cout << n1.getUrbanEntity(n1Vertex) << " \n";
            std::cout << "the place is already taken!\n";
            return -1;
        }
        if (!start) {
            Road *proadn1n2 = n1.getRoad(edgeSideOfN1ToN2);
            Road *proadn1n3 = n1.getRoad(edgeSideOfN1ToN3);
            Road *proadn2n3 = n2.getRoad(edgeSideOfN2ToN3);


            if ((proadn1n2 == nullptr || proadn1n2->getOwner() != owner) &&
                (proadn1n3 == nullptr || proadn1n3->getOwner() != owner) &&
                (proadn2n3 == nullptr || proadn2n3->getOwner() != owner)) {
                std::cout << "Invalid location! you have to place adjacent to one of your roads\n";
                return -1;
            }
        }
        if (n1.getUrbanEntity((n1Vertex + 1) % 6) || n1.getUrbanEntity((n1Vertex - 1 + 6) % 6) ||
            n2.getUrbanEntity((n2Vertex + 1) % 6) || n2.getUrbanEntity((n2Vertex - 1 + 6) % 6) ||
            n3.getUrbanEntity((n3Vertex + 1) % 6) || n3.getUrbanEntity((n3Vertex - 1 + 6) % 6)) {
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

        //update neighbors tiles
        // find mid tile
        if ((edgeSideOfN1ToN3 == DownRightEdge && edgeSideOfN1ToN2 == DownLeftEdge) ||
            (edgeSideOfN1ToN3 == DownLeftEdge && edgeSideOfN1ToN2 == DownRightEdge) ||
            (edgeSideOfN1ToN3 == UpRightEdge && edgeSideOfN1ToN2 == UpLeftEdge) ||
            (edgeSideOfN1ToN3 == UpLeftEdge && edgeSideOfN1ToN2 == UpRightEdge))
            neighborTileDown = &n1;

        else if ((edgeSideOfN2ToN3 == DownRightEdge && edgeSideOfN2ToN1 == DownLeftEdge) ||
                 (edgeSideOfN2ToN3 == DownLeftEdge && edgeSideOfN2ToN1 == DownRightEdge) ||
                 (edgeSideOfN2ToN3 == UpRightEdge && edgeSideOfN2ToN1 == UpLeftEdge) ||
                 (edgeSideOfN2ToN3 == UpLeftEdge && edgeSideOfN2ToN1 == UpRightEdge))
            neighborTileDown = &n2;
        else
            neighborTileDown = &n3;
        // find right edge
        if ((edgeSideOfN1ToN3 == DownLeftEdge && edgeSideOfN1ToN2 == LeftEdge) ||
            (edgeSideOfN1ToN3 == LeftEdge && edgeSideOfN1ToN2 == DownLeftEdge) ||
            (edgeSideOfN1ToN3 == UpLeftEdge && edgeSideOfN1ToN2 == LeftEdge) ||
            (edgeSideOfN1ToN3 == LeftEdge && edgeSideOfN1ToN2 == UpLeftEdge))
            neighborTileLeft = &n1;
        else if ((edgeSideOfN2ToN3 == DownLeftEdge && edgeSideOfN2ToN1 == LeftEdge) ||
                 (edgeSideOfN2ToN3 == LeftEdge && edgeSideOfN2ToN1 == DownLeftEdge) ||
                 (edgeSideOfN2ToN3 == UpLeftEdge && edgeSideOfN2ToN1 == LeftEdge) ||
                 (edgeSideOfN2ToN3 == LeftEdge && edgeSideOfN2ToN1 == UpLeftEdge))
            neighborTileLeft = &n2;
        else
            neighborTileLeft = &n3;
        // find left edge
        if ((edgeSideOfN1ToN3 == DownRightEdge && edgeSideOfN1ToN2 == RightEdge) ||
            (edgeSideOfN1ToN3 == RightEdge && edgeSideOfN1ToN2 == DownRightEdge) ||
            (edgeSideOfN1ToN3 == UpRightEdge && edgeSideOfN1ToN2 == RightEdge) ||
            (edgeSideOfN1ToN3 == RightEdge && edgeSideOfN1ToN2 == UpRightEdge))
            neighborTileRight = &n1;
        else if ((edgeSideOfN2ToN3 == DownRightEdge && edgeSideOfN2ToN1 == RightEdge) ||
                 (edgeSideOfN2ToN3 == RightEdge && edgeSideOfN2ToN1 == DownRightEdge) ||
                 (edgeSideOfN2ToN3 == UpRightEdge && edgeSideOfN2ToN1 == RightEdge) ||
                 (edgeSideOfN2ToN3 == RightEdge && edgeSideOfN2ToN1 == UpRightEdge))
            neighborTileRight = &n2;
        else
            neighborTileRight = &n3;


        return 0;

    }

    // Constructor for City
    // Parameters:
    // - owner: Pointer to the owner of the City
    City::City(Player *p) {
        this->owner = p;
        type = CITY;
        numOfResources = 2;
        numOfVictoryPoints = 2;
        neighborTileRight = nullptr;
        neighborTileLeft = nullptr;
        neighborTileDown = nullptr;
    }

    // Function to place a City on the board
    // Parameters:
    // - n1: First Tile
    // - n2: Second Tile
    // - n3: Third Tile
    // - start: Flag indicating if it's the start of the game (default: false)
    // Returns:
    // - 0 if the City is successfully placed, -1 otherwise
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
            int k = (i - 1 + 6) % 6;
            if (n1.getNeighbor(i) != nullptr || n1.getNeighbor(k) != nullptr)
                if ((*n1.getNeighbor(i) == n3 || *n1.getNeighbor(i) == n2) &&
                    (*n1.getNeighbor(k) == n3 || *n1.getNeighbor(k) == n2))
                    n1Vertex = i;
        }
        for (int i = 0; i < 6; ++i) { //find n2 vertex
            int k = (i - 1 + 6) % 6;
            if (n2.getNeighbor(i) != nullptr || n2.getNeighbor(k) != nullptr)
                if ((*n2.getNeighbor(i) == n1 || *n2.getNeighbor(i) == n3) &&
                    (*n2.getNeighbor(k) == n1 || *n2.getNeighbor(k) == n3))
                    n2Vertex = i;
        }
        for (int i = 0; i < 6; ++i) { //find n3 vertex
            int k = (i - 1 + 6) % 6;
            if (n3.getNeighbor(i) != nullptr || n3.getNeighbor(k) != nullptr)
                if ((*n3.getNeighbor(i) == n1 || *n3.getNeighbor(i) == n2) &&
                    (*n3.getNeighbor(k) == n1 || *n3.getNeighbor(k) == n2))
                    n3Vertex = i;

        }
        if (n1Vertex == -1 || n2Vertex == -1 || n3Vertex == -1) {
            std::cout << "the tiles are not adjacent(1)\n";
            return -1;
        }


        if (edgeSideOfN1ToN2 == -1 || edgeSideOfN1ToN3 == -1 || edgeSideOfN2ToN3 == -1) {
            std::cout << edgeSideOfN1ToN2 << ", " << edgeSideOfN1ToN3 << " , " << edgeSideOfN2ToN3 << " \n";
            std::cout << "the tiles are not adjacent(2)\n";
            return -1;
        }

        if (n1.getUrbanEntity(n1Vertex) == nullptr || n1.getUrbanEntity(n1Vertex)->getOwner() != owner) {
            std::cout << "Invalid location. the location have to contain one of your settlements\n";
            return -1;
        }


        int ans1 = n1.placeUrbanEntity(this, n1Vertex);
        int ans2 = n2.placeUrbanEntity(this, n2Vertex);
        int ans3 = n3.placeUrbanEntity(this, n3Vertex);
        if (ans1 == -1 || ans2 == -1 || ans3 == -1) {
            std::cout << "Invalid location! \n";
            return -1;
        }
        //update neighbors tiles
        // find mid tile
        if ((edgeSideOfN1ToN3 == DownRightEdge && edgeSideOfN1ToN2 == DownLeftEdge) ||
            edgeSideOfN1ToN3 == UpRightEdge && edgeSideOfN1ToN2 == UpLeftEdge)
            neighborTileDown = &n1;
        else if ((edgeSideOfN2ToN3 == DownRightEdge && edgeSideOfN2ToN1 == DownLeftEdge) ||
                 edgeSideOfN2ToN3 == UpRightEdge && edgeSideOfN2ToN1 == UpLeftEdge)
            neighborTileDown = &n2;
        else
            neighborTileDown = &n3;
        // find right edge
        if ((edgeSideOfN1ToN3 == DownLeftEdge && edgeSideOfN1ToN2 == LeftEdge) ||
            edgeSideOfN1ToN3 == UpLeftEdge && edgeSideOfN1ToN2 == LeftEdge)
            neighborTileLeft = &n1;
        else if ((edgeSideOfN2ToN3 == DownLeftEdge && edgeSideOfN2ToN1 == LeftEdge) ||
                 edgeSideOfN2ToN3 == UpLeftEdge && edgeSideOfN2ToN1 == LeftEdge)
            neighborTileLeft = &n2;
        else
            neighborTileLeft = &n3;
        // find left edge
        if ((edgeSideOfN1ToN3 == DownRightEdge && edgeSideOfN1ToN2 == RightEdge) ||
            edgeSideOfN1ToN3 == UpRightEdge && edgeSideOfN1ToN2 == RightEdge)
            neighborTileRight = &n1;
        else if ((edgeSideOfN2ToN3 == DownRightEdge && edgeSideOfN2ToN1 == RightEdge) ||
                 edgeSideOfN2ToN3 == UpRightEdge && edgeSideOfN2ToN1 == RightEdge)
            neighborTileRight = &n2;
        else
            neighborTileRight = &n3;

        return 0;

    }


//###################################    DEVELOPMENT CARDS    ###################################

    // a destructor (to avoid warning)
    DevelopmentCard::~DevelopmentCard() {}

    // returns the name of the card
    std::string DevelopmentCard::getName() {
        return name;
    }

    // a constructor for victor point development card
    VictoryPoint::VictoryPoint(Catan *gm) {
        this->name = "VictoryPoint";
        gameManager = gm;
    }

    // activate the card's effect - add 1 VP to the player
    // Parameters:
    // - p: a reference to the activating player
    void VictoryPoint::playCard(Player &p) {
        p.VictoryPoints++;
        std::cout << p.name << " played a victory point card and now have " << p.VictoryPoints << " points!\n";
    }

    // a constructor for knight point development card
    Knight::Knight(Catan *gm) {
        name = "Knight";
        gameManager = gm;
    }

    // activate the card's effect - add 1 Knight to the player
    // Parameters:
    // - p: a reference to the activating player
    void Knight::playCard(Player &p) {
        p.numOfKnights++;
        if (p.numOfKnights >= 3)
            p.VictoryPoints += 2;
    }

    // a constructor for monopoly development card
    Monopole::Monopole(Catan *gm) {
        name = "Monopole";
        gameManager = gm;
    }

    // activate the card's effect - takes from all the other players
    // all the resources of one type and gives it to the activating player
    // Parameters:
    // - p: a reference to the activating player
    void Monopole::playCard(Player &p) {
        int resource = -1;
        std::cout << "choose a resource for monopoly card(type a number):\n";
        while (resource < 0 || resource > 4) {
            std::cout << "BRICK: 0, IRON: 1, WHEAT: 2, WOOD: 3, WOOL: 4\n";
            std::cin >> resource;
        }
        this->gameManager->monopole(&p, resource);
    }

    // a constructor for roads build development card
    RoadsBuild::RoadsBuild(Catan *catan) {
        name = "RoadsBuild";
        gameManager = catan;
    }

    // activate the card's effect - lets the activating player place 2 roads
    // Parameters:
    // - p: a reference to the activating player
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
            int place = -1;

            while (place != 1 && place != 0) {
                std::cin.clear(); // Clear error flags
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                std::cout << "you have " << roadsToGet
                          << " to place. would you like to place the next road? (or pass) enter 1 to place, 0 to pass \n";
                std::cin >> place;
            }
            if (place == 0) {// pass
                std::cout << "passed 1 road\n";
                roadsToGet--;
            } else {

                std::cout << " choose where u want to place your road:\n";
                std::cout << " (choose two tiles and the road will build between them)\n";


                std::cout << "Choose where you want to place your road:\n"
                          << "(choose two tiles and the road will be built between them)\n";

                while (!validTile1) {
                    std::cout << "Tile 1:\n";
                    std::cout
                            << "----Enter the resource of the tile (0 - brick, 1-iron, 2- wheat, 3-wood, 4-wool,5-desert,6-sea):\n";
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
                            << "----Enter the resource of the tile (0 - brick, 1-iron, 2- wheat, 3-wood, 4-wool,5-desert,6-sea):\n";
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
    }

    // a constructor for year of plenty development card
    YearOfPlenty::YearOfPlenty(Catan *gm) {
        name = "YearOfPlenty";
        gameManager = gm;
    }

    // activate the card's effect - lets the activating player get 2 resources of his choice
    // Parameters:
    // - p: a reference to the activating player
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

    // Constructor for the Tile class.
    // Initializes a tile with a given number, resource type, and flags for sea and desert.
    Tile::Tile(int dieNum, std::string resource, bool issea = false, bool isDesert = false) {
        isSea = issea;
        this->isDesert = isDesert;
        this->resource = resource;
        number = dieNum;
        for (int i = 0; i < 6; ++i) {
            neighbors[i] = nullptr;
            urbanEntities[i] = nullptr;
            roads[i] = nullptr;
        }
    };

    // Updates the neighbor of the current tile on a specific side.
    // Throws an exception if the side is out of bounds.
    void Tile::UpdateNeighbor(Tile &neighbor, int side) {
        if (side > 5 || side < 0)
            throw std::invalid_argument("side should be between 0 to 5 (include 0 and 5)");
        neighbors[side] = &neighbor;
    }

    // Places an urban entity (Settlement or City) on the specified side of the tile.
    // Returns 0 if successful, -1 if the side is out of bounds.
    int Tile::placeUrbanEntity(UrbanEntity *UrbanEntity, int side) {
        if (side > 5 || side < 0) {
            std::cout << "side should be between 0 to 5 (include 0 and 5)\n";
            return -1;
        }
        if (UrbanEntity->getType() == CITY) {
            urbanEntities[side]->getOwner()->takeBackSettlement((Settlement *) urbanEntities[side]);
        }
        urbanEntities[side] = UrbanEntity;
        return 0;
    }

    // Places a road on the specified side of the tile.
    // Returns 0 if successful, -1 if the side is out of bounds.
    int Tile::placeRoad(Road *road, int side) {
        if (side > 5 || side < 0) {
            std::cout << "side should be between 0 to 5 (include 0 and 5)\n";
            return -1;
        }
        roads[side] = road;
        return 0;
    }

    // Retrieves the neighbor of the current tile on a specific side.
    // Throws an exception if the side is out of bounds.
    Tile *Tile::getNeighbor(int side) {
        if (side > 5 || side < 0)
            throw std::invalid_argument("side should be between 0 to 5 (including 0 and 5)");
        return neighbors[side];
    }

    // Retrieves the road on the specified side of the tile.
    // Throws an exception if the side is out of bounds.
    Road *Tile::getRoad(int side) {
        if (side > 5 || side < 0)
            throw std::invalid_argument("side should be between 0 to 5 (include 0 and 5)");
        return roads[side];
    }

    // Retrieves the urban entity (Settlement or City) on the specified side of the tile.
    // Throws an exception if the side is out of bounds.
    UrbanEntity *Tile::getUrbanEntity(int side) {
        if (side > 5 || side < 0)
            throw std::invalid_argument("side should be between 0 to 5 (include 0 and 5)");
        return urbanEntities[side];
    }

    // Retrieves the resource type of the tile.
    int Tile::getResource() {
        return convertResourceToInt(resource);
    }

    // Retrieves the number associated with the tile.
    int Tile::getNumber() {
        return number;
    }

    // Retrieves whether the tile is a sea tile.
    bool Tile::getIsSea() { return isSea; }

    // Retrieves whether the tile is a desert tile.
    bool Tile::getIsDesert() { return isDesert; }

    // Overloaded equality operator for comparing two tiles.
    bool operator==(const Tile &t1, const Tile &t2) {
        return (&t1 == &t2);
    }

    // Overloaded inequality operator for comparing two tiles.
    bool operator!=(const Tile &t1, const Tile &t2) {
        return &t1 != &t2;
    }

    // Overloaded stream insertion operator to print a tile.
    std::ostream &operator<<(std::ostream &os, const Tile &tile) {
        if (tile.isSea)
            os << "sea" << tile.number;
        else if (tile.isDesert)
            os << "desert ";
        else {
            os << tile.resource << " " << std::to_string(tile.number);
        }
        return os;
    }

//###################################   BOARD   ###################################
    // Constructor for the Board class.
    // Initializes the game board by placing tiles with resources and numbers, shuffling them,
    // ensuring no two tiles have the same resource and number combination,
    // placing a desert tile, adding sea tiles around the board, and updating tile neighbors.
    Board::Board(bool constant) {
        // Seed the random number generator
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        // numbers for the tiles
        std::vector<int> numbers = {2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12};

        // Shuffle the vector
        if (!constant) {
            std::shuffle(numbers.begin(), numbers.end(),
                         std::default_random_engine((unsigned long) std::time(nullptr)));
        }
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
        //check if there are two tiles with same resource and number
        bool done = false;
        while (!done) {
            done = true;
            for (unsigned int i = 0; i < tiles.size() && done; ++i) {
                for (unsigned int j = i + 1; j < tiles.size() && done; ++j) {
                    if (tiles[i]->getNumber() == tiles[j]->getNumber() &&
                        tiles[i]->getResource() == tiles[j]->getResource()) { // if there are two same tiles
                        // swap one tile's number with his neighbor (and we will check again)
                        done = false;
                        int temp = tiles[j]->getNumber();
                        tiles[j]->number = tiles[(j + 1) % tiles.size()]->getNumber();
                        tiles[(j + 1) % tiles.size()]->number = temp;
                    }
                }

            }
        }

        // desert tile
        Tile *desert = new Tile(5, "desert", false, true);
        tiles.push_back(desert);
        //shuffle the tiles
        if (!constant) {
            std::shuffle(tiles.begin(), tiles.end(), std::default_random_engine((unsigned long) std::time(nullptr)));
        }
        // 18 sea tiles
        unsigned int locationsForSea[18] = {0, 1, 2, 3, 4, 8, 9, 14, 15, 21, 22, 27,
                                            28, 32, 33, 34, 35, 36};
        unsigned int shift = 0;

        for (unsigned int i = 0; i < 18; ++i) {
            Tile *tile = new Tile((int) i, "sea", true, false);
            tiles.insert(tiles.begin() + locationsForSea[i], tile);
            shift++;

        }

        //update neighbors

        unsigned int rowSize[] = {4, 5, 6, 7, 6, 5, 4};
        int rowSizeLength = 7;
        shift = 0;
        // updating extra shift for the up/down half of the board
        // (because sometimes the row we go to is longer than row i by one and sometimes shorter by one)
        unsigned int leftUpMinus = 0;
        unsigned int rightUpPlus = 1;
        unsigned int downRightPlus = 1;
        unsigned int downLeftMinus = 0;

        // updating the neighbors of all the tiles
        for (unsigned int i = 0; i < rowSizeLength; ++i) {
            if (i != 0)
                shift += rowSize[i - 1];
            if (i == 4) {
                leftUpMinus = 1;
                rightUpPlus = 0;
            }
            if (i == 3) {
                downRightPlus = 0;
                downLeftMinus = 1;
            }
            // updating the neighbors of the tiles on row i
            for (unsigned int j = 0; j < rowSize[i]; ++j) {
                if (j != 0)
                    tiles[j + shift]->UpdateNeighbor(*tiles[shift + j - 1], LeftEdge);
                if (j != rowSize[i] - 1)
                    tiles[j + shift]->UpdateNeighbor(*tiles[shift + j + 1], RightEdge);

                if (i != 0 && (j != 0 || i >= 4))
                    tiles[j + shift]->UpdateNeighbor(*tiles[shift + j - rowSize[i] - leftUpMinus], UpLeftEdge);
                if (i != 0 && (i >= 4 || j + 1 != rowSize[i]))
                    tiles[j + shift]->UpdateNeighbor(*tiles[shift + j - rowSize[i] + rightUpPlus], UpRightEdge);

                if (i + 1 != rowSizeLength && (i < 4 || j + 1 != rowSize[i]))
                    tiles[j + shift]->UpdateNeighbor(*tiles[shift + j + rowSize[i] + downRightPlus], DownRightEdge);
                if (i + 1 != rowSizeLength && (i < 4 || j != 0))
                    tiles[j + shift]->UpdateNeighbor(*tiles[shift + j + rowSize[i] - downLeftMinus], DownLeftEdge);

            }
        }
    }

    // Destructor for the Board class.
    // Deallocates memory for each tile and clears the vector of tiles.
    Board::~Board() {
        // Deallocate memory for each tile
        for (Tile *tile: tiles) {
            delete tile;
        }
        // Clear the vector of tiles
        tiles.clear();
    }

    // Prints the Catan game board with tiles arranged in a hexagonal pattern.
    void Board::printBoard() {
        unsigned int first = 4;
        unsigned int second = 5;
        unsigned int third = 6;
        unsigned int fourth = 7;
        unsigned int fifth = 6;
        unsigned int sixth = 5;
        unsigned int seventh = 4;
        std::cout << "\n              ************ CATAN BOARD ************\n";
        std::cout << "                   ";
        for (unsigned int i = 0; i < first; ++i) { // first row
            std::cout << *tiles[i] << "   ";
        }
        std::cout << "\n               ";
        for (unsigned int i = first; i < first + second; ++i) { //second row
            std::cout << *tiles[i] << "  ";
        }
        std::cout << "\n           ";
        for (unsigned int i = first + second; i < first + second + third; ++i) { //third row
            std::cout << *tiles[i] << "  ";
        }
        std::cout << "\n       ";
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
        std::cout << "\n                   ";
        for (unsigned int i = first + second + third + fourth + fifth + sixth;
             i < first + second + third + fourth + fifth + sixth + seventh; ++i) { //seventh row
            std::cout << *tiles[i] << "   ";
        }
        std::cout << "\n             **************************************\n\n";
    }

    // Finds a tile with a specific number and resource type.
    // Returns a pointer to the tile if found, otherwise returns nullptr.
    Tile *Board::findTile(int numTile, int resourceTile) {
        for (Tile *t: tiles)
            if (t->getResource() == resourceTile && t->getNumber() == numTile)
                return t;
        return nullptr;
    }

    // Prints the neighbors of each tile on the board.
    // Neighbors are printed in a hexagonal pattern around each tile.(useful for debugging)
    void Board::printNeighbors() {
        for (unsigned int i = 0; i < tiles.size(); ++i) {
            std::cout << "" << std::endl;
            for (int j = 0; j < 6; ++j) {
                Tile *nbr = tiles[i]->getNeighbor(j);
                std::cout << "neighbor of tile " << i << " in side " << j << " is: ";

                if (nbr != nullptr)
                    std::cout << *nbr << " |  ";
                else
                    std::cout << "null | ";
            }
            std::cout << "\n";
            if (i == 3 || i == 8 || i == 14 || i == 21 || i == 27 || i == 32)
                std::cout << "---------------------------------------------------------------\n";
        }
    }


}