#pragma once
#include "shape.h"

class Z : public shape {
private:
    int position;

public:
    Z();

    void rotate(int arr[20][10]) override;
    void updateCoordinates() override;
};
