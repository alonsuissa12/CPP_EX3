//
// Created by alon on 5/20/24.
//

#ifndef CPP_EX3_24_MAIN_RESOURCES_H
#define CPP_EX3_24_MAIN_RESOURCES_H
#include "Board.h" //todo: pay attention for loop include!
#include "Player.h"
#include <string.h>

#define SETTLEMENT 2
#define CITY 1

class Road{
private:
    Player owner;
    Tile & neighborTile1; //todo: not sure if needed
    Tile & neighborTile2; //todo: not sure if needed
    Road & prevRoadEdge1;
    Road & prevRoadEdge2;
    Road & nextRoadEdge1;
    Road & nextRoadEdge2;
public:
    Road(Player owner,Tile & n1,Tile& n2);
    void updateNextRoad(Road &r);
    void updatePrevRoad(Road &r);

};

class UrbanEntity{
public:
    virtual Player& getOwner() =0 ;
    virtual int getNumOfResources() =0  ;
    virtual int getNumOfVictoryPoints() = 0;
    virtual Tile& getNeighbor(int num) = 0;
    virtual void place(Tile & n1,Tile & n2, Tile& n3) = 0;
    virtual int getType() = 0;

};

class Settlement:public UrbanEntity{
private:
    int type;
    Player& owner;
    int numOfResources;
    int numOfVictoryPoints;
    Tile & neighborTile1;
    Tile & neighborTile2;
    Tile & neighborTile3;
public:
    Settlement(Player &owner);
};

class City:public UrbanEntity{
private:
    int type;
    Player& owner;
    int numOfResources;
    int numOfVictoryPoints;
    Tile & neighborTile1;
    Tile & neighborTile2;
    Tile & neighborTile3;
public:
    City(Player &owner);

};

class DevelopmentCard{ //todo: make it interface and create inheriting types
private:
    std::string name;
public:
    virtual DevelopmentCard(std::string name) = 0;
    virtual void playCard(Player &p) = 0;

};
class DevelopmentCardsDeck{
private:
    std::vector<DevelopmentCard> deck;
    void shuffle(std::vector<DevelopmentCard>);
public:
    DevelopmentCardsDeck(); // todo: crate a deck with all the cards and shuffle it
    DevelopmentCard draw();
};


#endif //CPP_EX3_24_MAIN_RESOURCES_H
