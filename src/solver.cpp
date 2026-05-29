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

void    Solver::findPaths(void)
{
    std::vector<Room*> startPath;

    startPath.push_back(this->_anthill->getVestibule());
    this->_toExplore.push(startPath);

    while (!this->_toExplore.empty())
    {
        std::vector<Room*> currentPath = this->_toExplore.front();
        this->_toExplore.pop();

        Room *lastRoom = currentPath.back();

        if (lastRoom == this->_anthill->getDortoir())
        {
            this->_paths.push_back(currentPath);
            continue ;
        }

        std::vector<Room*> neighbors = lastRoom->getNeighbors();
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
    for (uint16_t i = 0; i < this->_anthill->getAntCount(); i++)
    {
        Ant *ant = new Ant();
        ant->setId(i + 1);
        ant->setName("f" + std::to_string(i + 1));
        ant->setRoomPtr(this->_anthill->getVestibule());
        this->_ants.push_back(ant);
    }

    uint16_t    antsInDortoir = 0;
    uint16_t    stepNumber = 0;

    while (antsInDortoir < this->_anthill->getAntCount())
    {
        std::vector<std::string>    currentStep;
        stepNumber++;

        for (uint16_t i = 0; i < this->_ants.size(); i++)
        {
            Ant     *ant = this->_ants[i];
            Room    *current = ant->getRoomPtr();

            if (current == this->_anthill->getDortoir())
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

                if (next == this->_anthill->getDortoir() ||
                    next->getAntsCount() < next->getRoomSize())
                {
                    current->removeAnt(ant);
                    next->addAnt(ant);
                    ant->setRoomPtr(next);

                    std::string move = ant->getName() + " - " +
                                      current->getName() + " - " +
                                      next->getName();
                    currentStep.push_back(move);

                    if (next == this->_anthill->getDortoir())
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