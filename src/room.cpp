#include "../include/Room.hpp"
#include <cstddef>
#include <cstdint>

Room::Room(void)
{
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

void Room::setNextRoomPtr(void *next_room_ptr)
{
    this->_nextRoom = next_room_ptr;
}

void Room::setPrevRoomPtr(void *prev_room_ptr)
{
    this->_prevRoom = prev_room_ptr;
}

void Room::setRoomSize(uint16_t size)
{
    this->_roomSize = size;
}

uint8_t Room::addAnt(Ant &ant)
{
    if (this->_antsCount != this->_roomSize)
    {
        this->_ants[this->_antsCount] = &ant;
        this->_antsCount++;
        return SUCESS;
    }
    else
    {
        return FULLROOM_ERR;
    }
}

uint8_t Room::removeAnt(Ant &ant)
{
    if (this->_antsCount != 0)
    {
        this->_ants[this->_antsCount] = nullptr;
        this->_antsCount--;
    }
    else
    {
        return EMPTYROOM_ERR;
    }
}
