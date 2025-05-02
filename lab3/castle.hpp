#ifndef CASTLE_HPP
#define CASTLE_HPP
#include "room.hpp"
#include <vector>

class castle
{
private:
    // room map[CASTLE_MAX_SIZE][CASTLE_MAX_SIZE];
    std::vector<room*> rooms;
    int size;
public:
    castle();
    ~castle();
    room* init(int capacity);
    void GameEnd(int end);
    void testFinder(std::string PrincessorMonster);
    int getSize();
    room* getRoom(int i);
};


#endif