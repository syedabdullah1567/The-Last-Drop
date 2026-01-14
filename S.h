#pragma once
#include "shape.h"

class S : public shape {
private:
    int position;

public:
    S();

    void rotate(int arr[20][10]) override;
    void updateCoordinates() override;
};
