#pragma once

#include <cstdint>
#include <list>
#include <string>
#include <vector>
#include "Ant.hpp"

enum ROOM_TYPE
{
    BEGIN_ROOM,
    NORMAL_ROOM,
    REST_ROOM
};

enum ERROR_TYPE
{
    SUCESS,
    FULLROOM_ERR,
    EMPTYROOM_ERR,
    ROOMNOTFOUND_ERR
};


class Room
{
    public:
        Room(void);
        ~Room();

        void            *getNextRoomPtr(void);
        void            *getPrevRoomPtr(void);
        uint16_t        getRoomSize(void);
        uint16_t        getAntsCount(void);
        std::string     getName(void);
        std::vector<Room*> getNeighbors(void);

        void            setNextRoomPtr(void *next_room_ptr);
        void            setPrevRoomPtr(void *prev_room_ptr);
        void            setRoomSize(uint16_t size);
        void            setName(std::string name);
        void            addNeighbor(Room *room);

        uint8_t         addAnt(Ant *ant);
        uint8_t         removeAnt(Ant *ant);

    private:
        void                *_nextRoom = nullptr;
        void                *_prevRoom = nullptr;
        uint16_t            _antsCount = 0;
        uint16_t            _roomSize;
        uint16_t            _roomNumber;
        std::string         _name;
        std::list<Ant>      _ants;
        std::vector<Room*>  _neighbors;
        uint8_t             _roomType;
};