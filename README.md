# Settlers of Catan: Modified Rules

## Objective
The goal of the game is to be the first player to reach 10 Victory Points.

## Setup
1. **Board Setup**: 
   - the board is generated randomly, the board contain tiles 
2. **Players**: The game is for 3 players.
3. **Starting Settlements**: Each player places two settlements and two roads on the board at the start of the game.
   - Each player places one settlement and one connecting road .
4. **Initial Resources**: Players receive resources based on the hexes their second settlement is adjacent to.

## Rules of Play

### Turn Sequence
1. **Roll for Resource Production**: The active player rolls two six-sided dice to determine which hexes produce resources.
   - Each hex with the rolled number produces resources for players with settlements or cities adjacent to it.
2. **Resource Collection**: Players collect resources from hexes adjacent to their settlements and cities based on the dice roll.
   - Settlements produce one resource; cities produce two resources.
3. **Trade**:
   - **Domestic Trade**: Players may trade resources with each other.
   - **Development Card Trade**: Players may trade development cards with each other as long as the cards have not been played yet.
   - **Bank Trade**: Players can trade resources with the bank at a 4:1 ratio.
4. **Build and Develop**: Players may build roads, settlements, or cities, and purchase or play development cards.
   - **Roads**: Cost 1 Brick and 1 Wood.
   - **Settlements**: Cost 1 Brick, 1 Wood, 1 Wheat, and 1 Sheep.
   - **Cities**: Cost 2 Wheat and 3 Ore.
   - **Development Cards**: Cost 1 Wheat, 1 Sheep, and 1 Ore.
5. **Play Development Cards**: Players may play one development card per turn, except the turn they buy it.

### Building
- **Roads**: Must connect to the player’s existing roads, settlements, or cities.
- **Settlements**: Must be at least two roads away from any other settlement.
- **Cities**: Upgrade an existing settlement.

### Development Cards
- Players draw development cards from the deck and may hold them for future use.
- Types of development cards include:
  - **Knight**: counts toward the grate army (without the robber effect)
  - **Victory Point**: Adds directly to a player’s score.
  - **Road Building**: Allows the player to place two free roads.
  - **Year of Plenty**: Allows the player to take any two resources from the bank.
  - **Monopoly**: Allows the player to claim all of one type of resource from other players.

### Victory Conditions
- The first player to reach 10 Victory Points on their turn wins the game.
- Victory Points are earned through:
  - Settlements: 1 point each
  - Cities: 2 points each
  - Victory Point cards: 1 point each
  - graet army (a player with 3 knight): 2 points

### Modifications to Standard Rules
1. **No Longest Road**: There is no bonus for the longest road.
2. **No Robber**: The robber is not used in the game.
3. **Three Players**: The game is exclusively for three players.
4. **Development Card Trading**: Players can trade development cards as long as they have not been played yet.
5. **No Ports**: There are no port trades available.

## How to Work with the Program

To interact with the program and play the game, follow these steps:

### Running the Program
1. **Compile and run the Program**: type in terminal the command: make catan
2. **note!** somtimes the command compile the files and fail to run it if thats the case close it with CTRL + C and try again
