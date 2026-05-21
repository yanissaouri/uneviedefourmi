#pragma once

#include <cstdint>
#include <list>
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

        void            setNextRoomPtr(void *next_room_ptr);
        void            setPrevRoomPtr(void *prev_room_ptr);
        void            setRoomSize(uint16_t size);

        uint8_t         addAnt(Ant *ant);
        uint8_t         removeAnt(Ant *ant);

    private:
        void            *_nextRoom = nullptr;
        void            *_prevRoom = nullptr;
        uint16_t        _antsCount = 0;
        uint16_t        _roomSize;
        uint16_t        _roomNumber;
        std::list<Ant>  _ants;
        uint8_t         _roomType;
};
