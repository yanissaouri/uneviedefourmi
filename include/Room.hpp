#pragma once

#include <cstdint>
#include <list>
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

        void            *getNextRoomPtr(int index);
        int             getNextRoomCount(void);
        void            *getPrevRoomPtr(int index);
        int             getPrevRoomCount(void);
        void            *getListNext(void);
        uint16_t        getRoomSize(void);
        uint16_t        getRoomNumber(void);
        uint16_t        getAntsCount(void);
        uint8_t         getRoomType(void);

        void            addNextRoomPtr(void *next_room_ptr);
        void            addPrevRoomPtr(void *prev_room_ptr);
        void            setListNext(void *next);
        void            setRoomSize(uint16_t size);
        void            setRoomNumber(uint16_t number);
        void            setRoomType(uint8_t type);

        uint8_t         addAnt(Ant *ant);
        uint8_t         removeAnt(Ant *ant);

    private:
        std::vector<void *> _nextRooms;
        std::vector<void *> _prevRooms;
        void                *_listNext = nullptr;
        uint16_t            _antsCount = 0;
        uint16_t            _roomSize = 0;
        uint16_t            _roomNumber = 0;
        std::list<Ant>      _ants;
        uint8_t             _roomType = NORMAL_ROOM;
};
