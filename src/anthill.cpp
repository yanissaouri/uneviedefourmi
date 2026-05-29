#include "../include/Anthill.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

Anthill::Anthill(void)
{
    this->_antCount = 0;
    this->_vestibule = nullptr;
    this->_dortoir = nullptr;
    return ;
}

Anthill::~Anthill(void)
{
    for (Room *room : this->_rooms)
        delete room;
    return ;
}

Room        *Anthill::getVestibule(void)
{
    return this->_vestibule;
}

Room        *Anthill::getDortoir(void)
{
    return this->_dortoir;
}

uint16_t    Anthill::getAntCount(void)
{
    return this->_antCount;
}

std::vector<Room*>  Anthill::getRooms(void)
{
    return this->_rooms;
}

std::vector<std::pair<Room*, Room*>>    Anthill::getTunnels(void)
{
    return this->_tunnels;
}

void    Anthill::addRoom(Room *room)
{
    this->_rooms.push_back(room);
    return ;
}

void    Anthill::addTunnel(Room *a, Room *b)
{
    this->_tunnels.push_back(std::make_pair(a, b));
    return ;
}

Room    *Anthill::getRoom(std::string name)
{
    if (this->_roomMap.find(name) != this->_roomMap.end())
        return this->_roomMap[name];
    return nullptr;
}

void    Anthill::loadFromFile(std::string filename)
{
    std::ifstream   file(filename);
    std::string     line;

    if (!file.is_open())
    {
        std::cerr << "Error: cannot open file " << filename << std::endl;
        return ;
    }

    // lire le nombre de fourmis
    std::getline(file, line);
    this->_antCount = std::stoi(line.substr(2));

    // créer vestibule et dortoir
    this->_vestibule = new Room();
    this->_vestibule->setName("Sv");
    this->_dortoir = new Room();
    this->_dortoir->setName("Sd");
    this->_roomMap["Sv"] = this->_vestibule;
    this->_roomMap["Sd"] = this->_dortoir;
    this->_rooms.push_back(this->_vestibule);
    this->_rooms.push_back(this->_dortoir);

    // lire les salles et tunnels
    while (std::getline(file, line))
    {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();

        std::cout << "ligne lue: [" << line << "]" << std::endl; // debug

        if (line.find(" - ") != std::string::npos)
        {
            // c'est un tunnel
            std::string nameA = line.substr(0, line.find(" - "));
            std::string nameB = line.substr(line.find(" - ") + 3);

            Room *a = this->getRoom(nameA);
            Room *b = this->getRoom(nameB);

            if (a && b)
            {
                this->addTunnel(a, b);
                a->addNeighbor(b);
                b->addNeighbor(a);
            }
        }
        else
        {
            // c'est une salle
            Room *room = new Room();
            room->setName(line);
            this->_roomMap[line] = room;
            this->_rooms.push_back(room);
        }
    }
    file.close();
    return ;
}