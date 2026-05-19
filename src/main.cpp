#include "../include/Room.hpp"
#include "../include/Ant.hpp"

#include <iostream>

int main(void)
{
    std::cout << "test";

    Room room[14];

    room[0].setRoomSize(8);
    room[1].setRoomSize(4);
    room[2].setRoomSize(2);
    room[3].setRoomSize(4);
    room[4].setRoomSize(2);
    room[5].setRoomSize(4);
    room[6].setRoomSize(2);
    room[7].setRoomSize(5);
    room[8].setRoomSize(0);
    room[9].setRoomSize(0);
    room[10].setRoomSize(0);
    room[11].setRoomSize(0);
    room[12].setRoomSize(4);
    room[13].setRoomSize(2);

    room[0].setNextRoomPtr(&room[1]);
    room[1].setNextRoomPtr(&room[2]);

    return 0;
}
