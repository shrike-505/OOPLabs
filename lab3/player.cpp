#include "player.hpp"
#include "castle.hpp"
#include <iostream>

std::string Directions[4]={
	"east",
	"west",
    "north",
    "south",
};
/**
 * Construct a player object, starting at the given room.
 *
 * The player has no beloved princess initially.
 * The room the player starts in is set to not have a princess or a monster.
 */
player::player(room* start)
    : currentRoom(*start), WithBelovedPrincess(false){
        currentRoom.setPrincessHere(false);
        currentRoom.setMonsterHere(false);
    }

player::~player()
{
}

void player::CheckforPrincess()
{
    if (currentRoom.Princess())
    {
        WithBelovedPrincess = true;
    }
}

/**
 * Play the game.
 *
 * If the player is in the lobby and has the beloved princess, the game
 * ends with a win. If the player is in a room with a monster, the game
 * ends with a loss.
 */
void player::play(castle game)
{
    while (true)
    {
        currentRoom.RoomInfo();
        if (WithBelovedPrincess && currentRoom.getName() == "lobby") {
            game.GameEnd(1);
            return;
        }
        else if(currentRoom.Monster()){
            game.GameEnd(2);
            return;
        }
        if (currentRoom.Princess())
        {
            if (!WithBelovedPrincess)
            {
                WithBelovedPrincess = true;
                std::cout << "Just Grab your beloved and leave." << std::endl;
            }
        }
        std::string direction;
        std::cout << "Where do you want to go?" << std::endl;
        std::cin >> direction;
        move(direction);
    }
}

/**
 * Move to the room in the given direction.
 *
 * If the direction is "cheat", print out the status of all exits
 * (monster and princess) and do not move.
 *
 * If the direction is not valid, print out an error message and do not move.
 *
 * Otherwise, move to the room in the given direction.
 *
 * @return true if the move is successful, false otherwise
 */
bool player::move(std::string direction)
{
    if(direction=="cheat"){
        for (auto const& x: Directions) {
            if (currentRoom.existExit(x))
                std::cout << "monster in " << x << ": " << currentRoom.getExit(x)->Monster() << std::endl;
        }
        for (auto const& x: Directions) {
            if (currentRoom.existExit(x))
                std::cout << "princess in " << x << ": " << currentRoom.getExit(x)->Princess() << std::endl;
        }
    } else {
        if(!currentRoom.existExit(direction)){
            std::cout << "No such direction here." << std::endl;
            return false;
        }
        else{
            currentRoom = *currentRoom.getExit(direction);
            return true;
        }
    }
    return false;
        
}

room player::getCurrentRoom()
{
    return currentRoom;
}

void player::setCurrentRoom(room r)
{
    currentRoom = r;
}
