#pragma once

#include <cstdint>
#include <vector>
#include <queue>
#include <string>

#include "Anthill.hpp"
#include "Ant.hpp"

class Solver
{
    public:
        Solver(void);
        ~Solver(void);

        void    setAnthill(Anthill *anthill);

        void    findPaths(void);
        void    simulate(void);
        void    printSteps(void);

    private:
        Anthill                             *_anthill;
        std::vector<Ant*>                   _ants;
        std::vector<std::vector<Room*>>     _paths;
        std::queue<std::vector<Room*>>      _toExplore;
        std::vector<std::vector<std::string>> _steps;
};