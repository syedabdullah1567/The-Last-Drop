#include "O.h"

O::O()
{
    position = 1;
    updateCoordinates();  // initialize arr
}

void O::rotate(int arrGrid[20][10])
{
    return;
}


void O::updateCoordinates() 
{
    arr.clear();

    arr.push_back({ y - 1, x });
    arr.push_back({ y,     x });
    arr.push_back({ y - 1, x - 1 });
    arr.push_back({ y, x - 1 });
}