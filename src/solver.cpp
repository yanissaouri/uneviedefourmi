#include "../include/Solver.hpp"
#include "../include/Room.hpp"
#include <iostream>

Solver::Solver(void)
{
    this->_anthill = nullptr;
    return ;
}

Solver::~Solver(void)
{
    for (Ant *ant : this->_ants)
        delete ant;
    return ;
}

void    Solver::setAnthill(Anthill *anthill)
{
    this->_anthill = anthill;
    return ;
}

static std::vector<Room*> getNeighbors(Room *room)
{
    std::vector<Room*> neighbors;
    for (int i = 0; i < room->getNextRoomCount(); i++)
        neighbors.push_back((Room*)room->getNextRoomPtr(i));
    for (int i = 0; i < room->getPrevRoomCount(); i++)
        neighbors.push_back((Room*)room->getPrevRoomPtr(i));
    return neighbors;
}

static std::string getRoomName(Room *room)
{
    uint8_t type = room->getRoomType();
    if (type == BEGIN_ROOM)
        return "Sv";
    if (type == REST_ROOM)
        return "Sd";
    return "S" + std::to_string(room->getRoomNumber());
}

void    Solver::findPaths(void)
{
    std::vector<Room*> startPath;

    startPath.push_back(this->_anthill->getStartRoom());
    this->_toExplore.push(startPath);

    while (!this->_toExplore.empty())
    {
        std::vector<Room*> currentPath = this->_toExplore.front();
        this->_toExplore.pop();

        Room *lastRoom = currentPath.back();

        if (lastRoom == this->_anthill->getEndRoom())
        {
            this->_paths.push_back(currentPath);
            continue ;
        }

        std::vector<Room*> neighbors = getNeighbors(lastRoom);
        for (Room *neighbor : neighbors)
        {
            bool visited = false;
            for (Room *room : currentPath)
            {
                if (room == neighbor)
                {
                    visited = true;
                    break ;
                }
            }
            if (!visited)
            {
                std::vector<Room*> newPath = currentPath;
                newPath.push_back(neighbor);
                this->_toExplore.push(newPath);
            }
        }
    }
    return ;
}

void    Solver::simulate(void)
{
    uint64_t antCount = this->_anthill->getTotalAntsCount();

    for (uint64_t i = 0; i < antCount; i++)
    {
        Ant *ant = new Ant();
        ant->setId((uint16_t)(i + 1));
        ant->setName("f" + std::to_string(i + 1));
        ant->setRoomPtr(this->_anthill->getStartRoom());
        this->_ants.push_back(ant);
    }

    uint64_t    antsInDortoir = 0;
    uint16_t    stepNumber = 0;

    while (antsInDortoir < antCount)
    {
        std::vector<std::string>    currentStep;
        stepNumber++;

        for (uint64_t i = 0; i < this->_ants.size(); i++)
        {
            Ant     *ant = this->_ants[i];
            Room    *current = ant->getRoomPtr();

            if (current == this->_anthill->getEndRoom())
                continue ;

            std::vector<Room*> path = this->_paths[i % this->_paths.size()];

            uint16_t pos = 0;
            for (uint16_t j = 0; j < path.size(); j++)
            {
                if (path[j] == current)
                {
                    pos = j;
                    break ;
                }
            }

            if (pos + 1 < path.size())
            {
                Room *next = path[pos + 1];

                if (next == this->_anthill->getEndRoom() ||
                    next->getRoomSize() == 0 ||
                    next->getAntsCount() < next->getRoomSize())
                {
                    current->removeAnt(ant);
                    next->addAnt(ant);
                    ant->setRoomPtr(next);

                    std::string move = ant->getName() + " - " +
                                      getRoomName(current) + " - " +
                                      getRoomName(next);
                    currentStep.push_back(move);

                    if (next == this->_anthill->getEndRoom())
                        antsInDortoir++;
                }
            }
        }
        if (!currentStep.empty())
            this->_steps.push_back(currentStep);
    }
    return ;
}

void    Solver::printSteps(void)
{
    for (uint16_t i = 0; i < this->_steps.size(); i++)
    {
        std::cout << "+++ E" << i + 1 << " +++" << std::endl;
        for (std::string move : this->_steps[i])
            std::cout << move << std::endl;
        std::cout << std::endl;
    }
    return ;
}
