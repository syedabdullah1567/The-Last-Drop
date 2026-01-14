#pragma once
#include "shape.h"

class L : public shape {
private:
    int position;

public:
    L();

    void rotate(int arr[20][10]) override;
    void updateCoordinates() override;
};
