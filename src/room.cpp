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

void *Room::getNextRoomPtr(int index)
{
    return this->_nextRooms[index];
}

int Room::getNextRoomCount(void)
{
    return (int)this->_nextRooms.size();
}

void *Room::getPrevRoomPtr(int index)
{
    return this->_prevRooms[index];
}

int Room::getPrevRoomCount(void)
{
    return (int)this->_prevRooms.size();
}

void *Room::getListNext(void)
{
    return this->_listNext;
}

uint16_t Room::getRoomSize(void)
{
    return this->_roomSize;
}

void Room::addNextRoomPtr(void *next_room_ptr)
{
    this->_nextRooms.push_back(next_room_ptr);
}

void Room::addPrevRoomPtr(void *prev_room_ptr)
{
    this->_prevRooms.push_back(prev_room_ptr);
}

void Room::setListNext(void *next)
{
    this->_listNext = next;
}

void Room::setRoomSize(uint16_t size)
{
    this->_roomSize = size;
}

void Room::setRoomNumber(uint16_t number)
{
    this->_roomNumber = number;
}

void Room::setRoomType(uint8_t type)
{
    this->_roomType = type;
}

uint16_t Room::getRoomNumber(void)
{
    return this->_roomNumber;
}

uint16_t Room::getAntsCount(void)
{
    return this->_antsCount;
}

uint8_t Room::getRoomType(void)
{
    return this->_roomType;
}

uint8_t Room::addAnt(Ant *ant)
{
    if (this->_roomSize > 0 && this->_antsCount >= this->_roomSize)
        return FULLROOM_ERR;
    this->_ants.push_back(*ant);
    this->_antsCount++;
    ant->setRoomPtr(this);
    return SUCESS;
}

uint8_t Room::removeAnt(Ant *ant)
{
    for (auto it = this->_ants.begin(); it != this->_ants.end(); ++it)
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
