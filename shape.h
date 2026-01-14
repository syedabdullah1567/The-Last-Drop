#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <vector>

using namespace std;
using namespace sf;

class shape 
{
protected:
    vector<pair<int, int>> arr;  // Stores shape block positions

    int x, y; // Central reference point / coordinate i.e every block's coordinate is set according to this

public:

    shape()
    {
        x = 4; // center top starting point
        y = 0;
    }
    

    // all virtual stuff done to ensure that the respective child class's functions get called

    virtual void rotate(int arr[20][10]) = 0;
    virtual void updateCoordinates() = 0;

    bool isWithinBounds(); // Ensures

    void clearFromGrid(int arrGrid[20][10]);

    bool lockTheShapeInTheGrid(int arrGrid[20][10], int shapeNum);

    bool isCollisionWithOtherShapes(int arrGrid[20][10]);

    void moveLeft(int arrGrid[20][10]);

    void moveRight(int arrGrid[20][10]);

    void moveDown(int arrGrid[20][10]);

    bool autoMoveDown(int arrGrid[20][10]);

    void printNextShape(int nextIndex, RenderWindow& gameplay, Font& font);

    void setMainArrayGrid(int arrGrid[20][10], int shapeNum);

    virtual ~shape() = 0; // Done to make shape an abstract class and call destructor of respective 
    // derived class assigned to it at the time and not its own destructor.

};
