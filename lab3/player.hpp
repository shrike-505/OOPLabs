#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "room.hpp"
#include "castle.hpp"

class player
{
private:
    room currentRoom;
    bool WithBelovedPrincess;
public:
    player(room* start);
    ~player();
    void CheckforPrincess();
    void play(castle game);
    bool move(std::string direction);
    room getCurrentRoom();
    void setCurrentRoom(room r);
};

#endif