#include "shape.h"

// This function checks whether all the blocks of the current shape
// are within the bounds of the 20x10 Tetris grid.
// If any block is outside the valid range, it returns false.
bool shape::isWithinBounds()
{
    for (vector<pair<int,int>>::iterator cell = arr.begin(); cell!=arr.end();cell++)
    {
        int row = cell->first;
        int col = cell->second;

        // Grid is 10 columns wide (0–9) and 20 rows high (0–19)
        if (col < 0 || col >= 10 || row >= 20)
            return false;
    }
    return true;
}

// Removes the shape's presence from the grid.
// This is necessary before moving or rotating the shape
// to avoid leaving trails or incorrect data.
void shape::clearFromGrid(int arrGrid[20][10])
{
    for (auto& cell : arr)
    {
        int row = cell.first;
        int col = cell.second;

        arrGrid[row][col] = 0; // Set grid cell to empty
    }
}

// Locks the shape into the grid when it reaches the bottom
// or lands on another shape. It checks:
// - If any block is already occupied (overlap) => lock immediately.
// - If the block is on the bottom row or resting on another shape,
//   it permanently writes the shape into the grid.
bool shape::lockTheShapeInTheGrid(int arrGrid[20][10], int shapeNum)
{
    for (auto& cell : arr)
    {
        int row = cell.first;
        int col = cell.second;

        //// If the cell is already filled, lock immediately
        //if (arrGrid[row][col] != 0) {
        //    return true; // Collision fallback
        //}

        // If the block is at the bottom or has another shape beneath it
        if (row >= 19 || arrGrid[row + 1][col] != 0)
        {
            // Set the shape's value in the grid
            setMainArrayGrid(arrGrid, shapeNum);
            return true;
        }
    }
    return false; // Not ready to lock yet
}

// Helper function used during left/right movement
// Checks if the shape is colliding with other locked shapes.
bool shape::isCollisionWithOtherShapes(int arrGrid[20][10])
{
    for (auto& cell : arr)
    {
        int row = cell.first;
        int col = cell.second;
        if (arrGrid[row][col] != 0)
            return true;
    }
    return false;
}

// Moves the shape one cell to the left
// Only commits move if it doesn't collide or go out of bounds
void shape::moveLeft(int arrGrid[20][10])
{
    x -= 1;
    updateCoordinates();
    if (!isWithinBounds() || isCollisionWithOtherShapes(arrGrid))
    {
        // Undo move if invalid
        x += 1;
        updateCoordinates();
    }
}

// Moves the shape one cell to the right with same safety checks
void shape::moveRight(int arrGrid[20][10]) {
    x += 1;
    updateCoordinates();
    if (!isWithinBounds() || isCollisionWithOtherShapes(arrGrid)) {
        x -= 1;
        updateCoordinates();
    }
}

// Moves the shape one cell downward manually (on key press)
void shape::moveDown(int arrGrid[20][10])
{
    y += 1;
    updateCoordinates();
    if (!isWithinBounds() || isCollisionWithOtherShapes(arrGrid))
    {
        y -= 1;
        updateCoordinates();
    }
}

// Moves the shape one cell down automatically (timed drop)
// Returns true if the move was valid, false if shape hit bottom/other blocks
bool shape::autoMoveDown(int arrGrid[20][10])
{
    y += 1;
    updateCoordinates();
    if (!isWithinBounds() || isCollisionWithOtherShapes(arrGrid))
    {
        // Undo move if invalid
        y -= 1;
        updateCoordinates();
        return false;
    }
    return true;
}

// Displays the preview of the next shape in a box on the left side
void shape::printNextShape(int nextIndex, RenderWindow& gameplay, Font& font)
{
    const float boxSize = 120.f;
    const float blockSize = 30.f;

    Vector2f boxPos(120.f, 215.f); // Position of preview box
    Vector2f boxCenter = boxPos + Vector2f(boxSize / 2, boxSize / 2);

    // Title text: "Next Shape"
    Text nextText;
    nextText.setFont(font);
    nextText.setString("Next Shape");
    nextText.setCharacterSize(24);
    nextText.setFillColor(Color::Red);
    nextText.setStyle(Text::Bold);
    FloatRect textBounds = nextText.getLocalBounds();
    nextText.setOrigin(textBounds.width / 2, textBounds.height / 2);
    nextText.setPosition(boxPos.x + boxSize / 2, boxPos.y - 30);
    gameplay.draw(nextText);

    // Drawing the preview box background
    RectangleShape previewBox(Vector2f(boxSize, boxSize));
    previewBox.setOutlineColor(Color::Black);
    previewBox.setFillColor(Color(0, 0, 0, 200)); // Transparent black
    previewBox.setOutlineThickness(5);
    previewBox.setPosition(boxPos);
    gameplay.draw(previewBox);

    // Setup block layout and color for each Tetrimino type
    Color color;
    vector<Vector2i> shapeBlocks;

    switch (nextIndex)
    {
    case 0: // I Shape
        color = Color::Cyan;
        shapeBlocks = { {0, -1}, {0, 0}, {0, 1}, {0, 2} };
        break;
    case 1: // J Shape
        color = Color::Blue;
        shapeBlocks = { {0, -1}, {0, 0}, {0, 1}, {-1, 1} };
        break;
    case 2: // L Shape
        color = Color(255, 165, 0); // Orange
        shapeBlocks = { {0, -1}, {0, 0}, {0, 1}, {1, 1} };
        break;
    case 3: // O Shape
        color = Color::Yellow;
        shapeBlocks = { {0, 0}, {1, 0}, {0, 1}, {1, 1} };
        break;
    case 4: // S Shape
        color = Color::Green;
        shapeBlocks = { {1, 0}, {0, 0}, {0, 1}, {-1, 1} };
        break;
    case 5: // T Shape
        color = Color(160, 32, 240); // Purple
        shapeBlocks = { {-1, 0}, {0, 0}, {1, 0}, {0, 1} };
        break;
    case 6: // Z Shape
        color = Color::Red;
        shapeBlocks = { {-1, 0}, {0, 0}, {0, 1}, {1, 1} };
        break;
    default: return;
    }

    // Draw each block of the preview shape
    for (auto& blockPos : shapeBlocks)
    {
        RectangleShape block(Vector2f(blockSize - 2, blockSize - 2)); // Slight spacing between blocks
        block.setFillColor(color);
        block.setOutlineThickness(1);
        block.setOutlineColor(Color(10, 50, 50));

        // Calculate position relative to the box center
        float x = boxCenter.x + blockPos.x * blockSize - 25;
        float y = boxCenter.y + blockPos.y * blockSize - 25;

        block.setPosition(x, y);
        gameplay.draw(block);
    }
}

// Writes the shape's position into the main 2D grid
// Each cell is marked with a number (1–7) representing the shape type
void shape::setMainArrayGrid(int arrGrid[20][10], int shapeNum)
{
    for (auto& cell : arr)
    {
        int row = cell.first;
        int col = cell.second;

        // Write only if not already filled — avoids overwriting
        if (arrGrid[row][col] == 0)
            arrGrid[row][col] = shapeNum;
    }
}

// Destructor for base class
shape::~shape() {}
