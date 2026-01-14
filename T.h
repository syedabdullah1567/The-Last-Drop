#pragma once
#include "shape.h"

class T : public shape {
private:
    int position;

public:
    T();

    void rotate(int arr[20][10]) override;
    void updateCoordinates() override;
};
