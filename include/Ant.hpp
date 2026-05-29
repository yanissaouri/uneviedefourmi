#pragma once

#include <cstdint>
#include <string>

class Room;

class Ant
{
    public:
        Ant();
        ~Ant();

        uint16_t    getId(void);
        std::string getName(void);
        Room        *getRoomPtr(void);

        void        setId(uint16_t id);
        void        setName(std::string name);
        void        setRoomPtr(Room *room_ptr);

    private:
        bool        _isWaiting;
        uint16_t    _id;
        std::string _name;
        Room        *_roomPtr;
};