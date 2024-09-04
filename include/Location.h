//
// Created by leth1 on 7/12/2024.
//

#ifndef CHESS_LOCATION_H
#define CHESS_LOCATION_H
struct Location
{
    int row;
    int column;

    Location(int r, int c) : row(r), column(c) {}
    Location();

};
#endif //CHESS_LOCATION_H