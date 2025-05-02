#include "room.hpp"
#include <iostream>

room::room(std::string n)
{
    name = n;
    isPrincessHere = false;
    isMonsterHere = false;
}

room::~room()
{
}

/**
 * Display information about the current room.
 *
 * This function prints the name of the room, whether the princess is
 * present, and a message about the scene. It also checks if there is
 * a monster in the room and prints a warning if so. Finally, it lists
 * all available exits from the room.
 */

void room::RoomInfo()
{
    std::cout << "You entered " << name << "." << std::endl;
    std::cout << "Princess " << (Princess()?"is":"is not") << " here. What a " << (Princess()?"lucky":"poor") << " scene." << std::endl;
    if(Monster()){
        std::cout << "Oops, you meet a monster, see ya on the other side." << std::endl;
    }
    std::cout << "This room has " << Exits.size() << " exits, which are: ";
    for (auto const& x : Exits) {
        std::cout << x.first << " ";
    }
    std::cout << std::endl;
}

bool room::Princess()
{
    return isPrincessHere;
}

bool room::Monster()
{
    return isMonsterHere;
}

void room::setExit(std::string dir, room *r)
{
    Exits[dir] = r;
}

bool room::existExit(std::string dir)
{
    return Exits.count(dir) > 0;
}

room *room::getExit(std::string dir)
{
    return Exits[dir];
}

void room::setPrincessHere(bool b)
{
    isPrincessHere = b;
}

void room::setMonsterHere(bool b)
{
    isMonsterHere = b;
}

std::string room::getName()
{
    return name;
}
