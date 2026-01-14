#include "I.h"

// Constructor for the I shape
I::I()
{
    position = 1;          // Initial orientation of the shape (horizontal or vertical)
    updateCoordinates();   // Initialize shape's coordinates based on position and (x, y)
}

// Rotates the I shape, checks for collisions or out-of-bounds after rotation
void I::rotate(int arrGrid[20][10])
{
    // Backup current position and coordinates in case we need to revert
    int oldPosition = position;
    vector<pair<int, int>> oldArr = arr;

    // Toggle position between 1 and 2 (horizontal <-> vertical)
    if (position == 1)
        position = 2;
    else
        position = 1;

    updateCoordinates(); // Update arr with new rotation coordinates

    // Validate the new rotation by checking bounds and collisions
    for (auto& cell : arr)
    {
        int row = cell.first;
        int col = cell.second;

        // If out of grid boundaries, revert to old state
        if (col < 0 || col >= 10 || row < 0 || row >= 20)
        {
            position = oldPosition;
            arr = oldArr;
            return;
        }

        // If collides with already locked shapes in the grid
        if (arrGrid[row][col] == 1)
        {
            position = oldPosition;
            arr = oldArr;
            return;
        }
    }

    // If no issues, new rotation is kept
}

// Updates the coordinates of the I shape blocks depending on the orientation
void I::updateCoordinates()
{
    arr.clear(); // Clear previous block positions

    if (position == 1)
    {
        // Vertical orientation of 'I' (column)
        arr.push_back({ y - 1, x });  // one block above center
        arr.push_back({ y,     x });  // center block
        arr.push_back({ y + 1, x });  // one block below center
        arr.push_back({ y + 2, x });  // two blocks below center
    }
    else
    {
        // Horizontal orientation of 'I' (row)
        arr.push_back({ y, x - 1 });  // one block left of center
        arr.push_back({ y, x });      // center block
        arr.push_back({ y, x + 1 });  // one block right of center
        arr.push_back({ y, x + 2 });  // two blocks right of center
    }
}
