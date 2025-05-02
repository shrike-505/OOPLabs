#ifndef ROOM_HPP
#define ROOM_HPP
#include <string>
#include <map>
#include <vector>
class room
{
private:
    /* data */
    std::string name;
    bool isPrincessHere;
    bool isMonsterHere;
    std::map<std::string, room*> Exits;
public:
    room(std::string n);
    ~room();
    void RoomInfo();
    bool Princess();
    bool Monster();
    void setExit(std::string dir, room* r);
    bool existExit(std::string dir);
    room* getExit(std::string dir);
    void setPrincessHere(bool b);
    void setMonsterHere(bool b);
    std::string getName();
};


#endif