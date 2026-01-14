#include "T.h"

T::T()
{
    position = 1;
    updateCoordinates();  // initialize arr
}

void T::rotate(int arrGrid[20][10])
{
    // Store the original position
    int oldPosition = position;
    vector<pair<int, int>> oldArr = arr;

    // Try rotating
    if (position == 1)
        position = 2;
    else if (position == 2)
        position = 3;
    else if (position == 3)
        position = 4;
    else
        position = 1;

    updateCoordinates(); // generate new coordinates

    // Check if new rotation is valid
    for (auto& cell : arr)
    {
        int row = cell.first;
        int col = cell.second;

        // Wall or bottom boundary collision
        if (col < 0 || col >= 10 || row < 0 || row >= 20)
        {
            // Restore original
            position = oldPosition;
            arr = oldArr;
            return;
        }

        // Collision with locked blocks in grid
        if (arrGrid[row][col] == 1)
        {
            // Restore original
            position = oldPosition;
            arr = oldArr;
            return;
        }
    }

    // No collision detected — keep new rotation
}

void T::updateCoordinates()
{
    arr.clear();

    if (position == 1)
    {
        arr.push_back({ y - 1, x });
        arr.push_back({ y,     x });
        arr.push_back({ y - 1, x + 1});
        arr.push_back({ y - 1, x - 1 });
    }
    else if (position == 2)
    {
        arr.push_back({ y, x - 1 });
        arr.push_back({ y, x });
        arr.push_back({ y+ 1, x });
        arr.push_back({ y - 1, x });
    }
    else if (position == 3)
    {
        arr.push_back({ y, x - 1 });
        arr.push_back({ y - 1, x });
        arr.push_back({ y, x });
        arr.push_back({ y, x + 1 });
    }
    else if (position == 4)
    {
        arr.push_back({ y - 1, x - 1 });
        arr.push_back({ y, x });
        arr.push_back({ y, x - 1 });
        arr.push_back({ y + 1, x - 1 });
    }
}
