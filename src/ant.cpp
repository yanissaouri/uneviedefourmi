#include "../include/Ant.hpp"

Ant::Ant() : _isWaiting(false), _id(0), _roomPtr(nullptr) {}

Ant::~Ant() {}

uint16_t Ant::getId(void)
{
    return this->_id;
}

std::string Ant::getName(void)
{
    return this->_name;
}

void Ant::setId(uint16_t id)
{
    this->_id = id;
}

void Ant::setName(std::string name)
{
    this->_name = name;
}

Room *Ant::getRoomPtr(void)
{
    return this->_roomPtr;
}

void Ant::setRoomPtr(Room *room)
{
    this->_roomPtr = room;
}
