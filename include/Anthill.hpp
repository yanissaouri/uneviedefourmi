#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <utility>

#include "Room.hpp"
#include "Ant.hpp"

class Anthill
{
    public:
        Anthill(void);
        ~Anthill(void);

        Room        *getVestibule(void);
        Room        *getDortoir(void);
        uint16_t    getAntCount(void);
        std::vector<Room*>                      getRooms(void);
        std::vector<std::pair<Room*, Room*>>    getTunnels(void);

        void        addRoom(Room *room);
        void        addTunnel(Room *a, Room *b);
        Room        *getRoom(std::string name);
        void        loadFromFile(std::string filename);

    private:
        uint16_t                                _antCount;
        Room                                    *_vestibule;
        Room                                    *_dortoir;
        std::vector<Room*>                      _rooms;
        std::vector<std::pair<Room*, Room*>>    _tunnels;
        std::map<std::string, Room*>            _roomMap;
};