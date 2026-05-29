#include "../include/Anthill.hpp"
#include "../include/Solver.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./uneviedefourmi <fichier>" << std::endl;
        return 1;
    }

    Anthill anthill;
    anthill.loadFromFile(argv[1]);

    std::cout << "Ant count: " << anthill.getAntCount() << std::endl;
    std::cout << "Rooms: " << anthill.getRooms().size() << std::endl;
    std::cout << "Tunnels: " << anthill.getTunnels().size() << std::endl;

    Solver solver;
    solver.setAnthill(&anthill);
    solver.findPaths();
    solver.simulate();
    solver.printSteps();

    return 0;
}