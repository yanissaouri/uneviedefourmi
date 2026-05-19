#pragma once

#include <cstdint>
#include "Ant.hpp"

enum ROOM_TYPE
{
    BEGIN_ROOM,
    NORMAL_ROOM,
    REST_ROOM
};

class Room
{
    public:
        Room();
        ~Room();

        void        *getNextRoomPtr(void);
        void        *getPrevRoomPtr(void);
        uint16_t    getRoomSize(void);

        void        setNextRoomPtr(void *next_room_ptr);
        void        setPrevRoomPtr(void *prev_room_ptr);
        void        setRoomSize(uint16_t size);

        uint8_t     addAnt(Ant &ant);
        void        removeAnt(Ant &ant);

    private:
        void        *_nextRoom;
        void        *_prevRoom;
        uint16_t    _roomSize;
        void        **_ants;
        uint8_t     roomType;
};
