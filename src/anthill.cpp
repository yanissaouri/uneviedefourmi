#include "../include/Anthill.hpp"

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>

Anthill::Anthill()
{
    return ;
}

Anthill::~Anthill()
{
    Room *current = this->_roomListHead;
    while (current)
    {
        Room *next = (Room *)(current->getListNext());
        delete current;
        current = next;
    }
}

uint8_t Anthill::openFile(char *file_path)
{
    std::ifstream file(file_path);
    std::string line;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            this->_file.push_back(line);
        }


        file.close();
    }
    else
    {
        return 1;
    }

    return 0;
}

static Room *findRoom(Room *head, uint16_t number)
{
    for (Room *r = head; r != nullptr; r = static_cast<Room *>(r->getListNext()))
    {
        if (r->getRoomNumber() == number)
            return r;
    }
    return nullptr;
}

static uint16_t parseRoomNb(const std::string &s)
{
    if (s.size() < 2)
        return 0;
    if (s[1] == 'v')
        return 0;
    if (s[1] == 'd')
        return UINT16_MAX;

    return (uint16_t)std::atoi(s.c_str() + 1);
}

uint8_t Anthill::parseAntsCount(void)
{
    if (!strstr(this->_file[0].c_str(), "f="))
        return 1;
    this->_totalAntsCount = atoi(this->_file[0].substr(2).c_str());
    return 0;
}

size_t Anthill::parseRooms(void)
{
    size_t  line_index = 1;
    Room    *startRoom = new Room();
    Room    *endRoom = new Room();
    Room    *tail = startRoom;

    startRoom->setRoomType(NORMAL_ROOM);
    startRoom->setRoomNumber(0);
    this->_roomListHead = startRoom;

    while (line_index < this->_file.size())
    {
        const std::string   &line = this->_file[line_index];

        if (line.empty() || strstr(line.c_str(), " - "))
            break;

        if (line[0] == 'S' && std::isdigit((unsigned char)line[1]))
        {
            Room        *room = new Room();
            uint16_t    room_nb = (uint16_t)std::atoi(line.c_str() + 1);

            room->setRoomNumber(room_nb);
            room->setRoomType(NORMAL_ROOM);

            size_t brace_pos = line.find('{');
            if (brace_pos != std::string::npos)
                room->setRoomSize((uint16_t)std::atoi(line.c_str() + brace_pos + 1));
            else
                room->setRoomSize(1);

            tail->setListNext(room);
            tail = room;
        }
        line_index++;
    }

    endRoom->setRoomType(NORMAL_ROOM);
    endRoom->setRoomNumber(UINT16_MAX);
    tail->setListNext(endRoom);

    return line_index;
}

void Anthill::parseTunnels(size_t line_index)
{
    while (line_index < this->_file.size())
    {
        const std::string   &line = this->_file[line_index];
        size_t              sep = line.find(" - ");

        if (sep != std::string::npos)
        {
            std::string     left = line.substr(0, sep);
            std::string     right = line.substr(sep + 3);
            uint16_t        left_nb = parseRoomNb(left);
            uint16_t        right_nb = parseRoomNb(right);

            Room *from = findRoom(this->_roomListHead, left_nb);
            Room *to   = findRoom(this->_roomListHead, right_nb);
            if (from && to)
            {
                if (left[1] == 'v')
                {
                    from->setRoomType(BEGIN_ROOM);
                    this->_startRoom = from;
                }
                else if (left[1] == 'd')
                {
                    from->setRoomType(REST_ROOM);
                    this->_endRoom = from;
                }
                if (right[1] == 'v')
                {
                    to->setRoomType(BEGIN_ROOM);
                    this->_startRoom = to;
                }
                else if (right[1] == 'd')
                {
                    to->setRoomType(REST_ROOM);
                    this->_endRoom = to;
                }
                from->addNextRoomPtr(to);
                to->addPrevRoomPtr(from);
            }
        }
        line_index++;
    }
}

uint8_t Anthill::parseText(void)
{
    if (this->parseAntsCount())
        return 1;
    size_t tunnel_start = this->parseRooms();
    this->parseTunnels(tunnel_start);
    return 0;
}

uint64_t Anthill::getTotalAntsCount(void)
{
    return this->_totalAntsCount;
}

Room *Anthill::getRoomList(void)
{
    return this->_roomListHead;
}

Room *Anthill::getStartRoom(void)
{
    return this->_startRoom;
}

Room *Anthill::getEndRoom(void)
{
    return this->_endRoom;
}
