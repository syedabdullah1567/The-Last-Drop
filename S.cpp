#include "S.h"

S::S()
{
    position = 1;
    updateCoordinates();  // initialize arr
}

void S::rotate(int arrGrid[20][10])
{
    // Store the original position
    int oldPosition = position;
    vector<pair<int, int>> oldArr = arr;

    // Try rotating
    if (position == 1)
        position = 2;
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


void S::updateCoordinates() {
    arr.clear();

    if (position == 1) {
        // Vertical I (rotated form)
        arr.push_back({ y - 1, x });  // one above center
        arr.push_back({ y,     x });  // center
        arr.push_back({ y - 1, x + 1});  // one below center
        arr.push_back({ y, x - 1 });  // two below center
    }
    else {
        // Horizontal I
        arr.push_back({ y - 1, x - 1 });  // one left of center
        arr.push_back({ y, x });      // center
        arr.push_back({ y, x - 1 });  // one right of center
        arr.push_back({ y + 1,x });  // two right of center
    }
}
