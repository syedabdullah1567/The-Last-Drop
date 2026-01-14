#pragma once
#include "shape.h"

class J : public shape {
private:
    int position;

public:
    J();

    void rotate(int arr[20][10]) override;
    void updateCoordinates() override;
};
