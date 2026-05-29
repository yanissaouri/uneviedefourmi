#include "../include/Ant.hpp"

Ant::Ant(void)
{
    this->_id = 0;
    this->_name = "";
    this->_roomPtr = nullptr;
    this->_isWaiting = false;
    return ;
}

Ant::~Ant(void)
{
    return ;
}

uint16_t    Ant::getId(void)
{
    return this->_id;
}

std::string Ant::getName(void)
{
    return this->_name;
}

Room        *Ant::getRoomPtr(void)
{
    return this->_roomPtr;
}

void        Ant::setId(uint16_t id)
{
    this->_id = id;
    return ;
}

void        Ant::setName(std::string name)
{
    this->_name = name;
    return ;
}

void        Ant::setRoomPtr(Room *room_ptr)
{
    this->_roomPtr = room_ptr;
    return ;
}