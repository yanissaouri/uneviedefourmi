#include "../include/Anthill.hpp"
#include "../include/Solver.hpp"

#include <iostream>

int main(int argc, char **argv)
{
    Anthill test;

    if (argc != 2)
    {
        std::cerr << "Need to enter the .txt file." << std::endl;
        return 1;
    }

    if (test.openFile(argv[1]))
    {
        std::cerr << "Unable to open file!" << std::endl;
        return 1;
    }

    if (test.parseText())
    {
        std::cerr << ".txt file is incorrect." << std::endl;
        return 1;
    }

    Solver solver;
    solver.setAnthill(&test);
    solver.findPaths();
    solver.simulate();
    solver.printSteps();

    return 0;
}
