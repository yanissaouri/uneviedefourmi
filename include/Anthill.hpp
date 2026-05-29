#pragma once

#include <cstdint>
#include <iostream>
#include <vector>
#include "Room.hpp"

class Anthill
{
    public:
        Anthill();
        ~Anthill();

        uint8_t                                     openFile(char *file_path);
        uint8_t                                     parseText(void);

        uint64_t                                    getTotalAntsCount(void);
        Room                                        *getRoomList(void);
        Room                                        *getStartRoom(void);
        Room                                        *getEndRoom(void);

    private:
        uint8_t                                     parseAntsCount(void);
        size_t                                      parseRooms(void);
        void                                        parseTunnels(size_t line_index);

        std::vector<std::string>                    _file;
        uint64_t                                    _totalAntsCount;
        Room                                        *_roomListHead = nullptr;
        Room                                        *_startRoom = nullptr;
        Room                                        *_endRoom = nullptr;
};
