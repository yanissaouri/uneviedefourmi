#include "../include/Room.hpp"
#include <cstddef>
#include <cstdint>

Room::Room(void)
{
    this->_name = "";
    this->_antsCount = 0;
    this->_roomSize = 1;
    this->_roomType = NORMAL_ROOM;
    return ;
}

Room::~Room()
{
    return ;
}

void *Room::getNextRoomPtr(void)
{
    return this->_nextRoom;
}

void *Room::getPrevRoomPtr(void)
{
    return this->_prevRoom;
}

uint16_t Room::getRoomSize(void)
{
    return this->_roomSize;
}

uint16_t Room::getAntsCount(void)
{
    return this->_antsCount;
}

std::string Room::getName(void)
{
    return this->_name;
}

std::vector<Room*> Room::getNeighbors(void)
{
    return this->_neighbors;
}

void Room::setNextRoomPtr(void *next_room_ptr)
{
    this->_nextRoom = next_room_ptr;
    return ;
}

void Room::setPrevRoomPtr(void *prev_room_ptr)
{
    this->_prevRoom = prev_room_ptr;
    return ;
}

void Room::setRoomSize(uint16_t size)
{
    this->_roomSize = size;
    return ;
}

void Room::setName(std::string name)
{
    this->_name = name;
    return ;
}

void Room::addNeighbor(Room *room)
{
    this->_neighbors.push_back(room);
    return ;
}

uint8_t Room::addAnt(Ant *ant)
{
    if (this->_antsCount < this->_roomSize)
    {
        this->_ants.push_back(*ant);
        this->_antsCount++;
        return SUCESS;
    }
    else
    {
        return FULLROOM_ERR;
    }
}

uint8_t Room::removeAnt(Ant *ant)
{
    if (this->_antsCount == 0)
        return EMPTYROOM_ERR;

    for (std::list<Ant>::iterator it = this->_ants.begin(); it != this->_ants.end(); it++)
    {
        if (it->getId() == ant->getId())
        {
            this->_ants.erase(it);
            this->_antsCount--;
            return SUCESS;
        }
    }
    return EMPTYROOM_ERR;
}