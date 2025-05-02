#include "castle.hpp"
#include "room.hpp"
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <set>
#define CASTLE_MAX_SIZE 20 // 20 rooms

// frequently used operators
std::string Direction[4]={
	"east",
	"west",
    "north",
    "south",
};
castle::castle()
{
    std::cout << "Hello, her hero." << std::endl;
}

castle::~castle()
{   
    while(!rooms.empty()){
        std::vector<room*>::iterator it = rooms.end();
        rooms.pop_back();
        delete (*it);        
    }
    std::cout << "Bye, my hero...";
}


/**
 * Initialize the castle with a given capacity.
 *
 * The castle will be filled with that many rooms, and the exits
 * will be set randomly. The Princess and Monster will also be
 * randomly placed in the castle.
 *
 * @param[in] capacity The number of rooms in the castle.
 *
 * @return The starting room of the castle.
 */
room* castle::init(int capacity){
    size = capacity;
    room* start = new room("lobby");    
    rooms.push_back(start);
    for (int i = 1; i < capacity; i++) {
        rooms.push_back(new room("normalRoom"));
    }

    // Randomly Set Princess and Monster
    int princessRoom = rand() % capacity;
    int monsterRoom = rand() % capacity;
    while (monsterRoom == princessRoom) {
        monsterRoom = rand() % capacity;
        // Make sure princess and monster are not in the same room
    }
    rooms[princessRoom]->setPrincessHere(true);
    rooms[monsterRoom]->setMonsterHere(true);
    // printf("Princess Room: %d, Monster Room: %d\n", princessRoom, monsterRoom); // Test Output

    // Randomly Set Exits
    for(int i = 0; i < capacity; i++){
        std::set<std::string> usedDirections;
        std::set<std::pair<int, int> > usedConnections;
        while (usedDirections.size() < 2) {  // Ensure at least one exit per room
            int direction = rand() % 4;
            std::string dir = Direction[direction];
            if (usedDirections.find(dir) == usedDirections.end()) {
                int nextRoomIndex = (i + 1 + rand() % (capacity - 1)) % capacity;
                if (usedConnections.find(std::make_pair(i, nextRoomIndex)) == usedConnections.end() && usedConnections.find(std::make_pair(nextRoomIndex, i)) == usedConnections.end()) {
                    rooms[i]->setExit(dir, rooms[nextRoomIndex]);
                    // Set the opposite exit for the next room
                    std::string oppositeDir;
                    if (dir == "east") oppositeDir = "west";
                    else if (dir == "west") oppositeDir = "east";
                    else if (dir == "south") oppositeDir = "north";
                    else if (dir == "north") oppositeDir = "south";
                    rooms[nextRoomIndex]->setExit(oppositeDir, rooms[i]);
                    usedDirections.insert(dir);
                    usedConnections.insert(std::make_pair(i, nextRoomIndex));
                    usedConnections.insert(std::make_pair(nextRoomIndex, i));
                }
            }
        }
    }
    // testFinder("Princess"); // Test Output
    return start;
}



/**
 * Prints a message depending on the game's end.
 *
 * @param[in] _end The reason of the game's end.
 *                  1: the player found the princess and escaped.
 *                  2: the player met a monster and died.
 */
void castle::GameEnd(int _end){
    if(_end == 1){
        std::cout << "Princess is here, u win and safely escape." << std::endl;
        return;
    }
    if(_end == 2){
        std::cout << "You meet a monster, u lose and die." << std::endl;
        return;
    }
}

void castle::testFinder(std::string PrincessorMonster)
{
    for(int i = 0; i < getSize(); i++){
        if(rooms[i]->Princess()){
            std::cout << "Princess is here." << std::endl;
        }
        if(rooms[i]->Monster()){
            std::cout << "Monster is here." << std::endl;
        }
    }
}

/**
 * Returns the size of the castle (number of rooms).
 *
 * @return The size of the castle.
 */
int castle::getSize()
{
    return size;
}


/**
 * Returns a room in the castle by its index.
 *
 * @param[in] i The index of the room to return.
 *
 * @return The room at index i.
 */
room *castle::getRoom(int i)
{
    return rooms[i];
}
