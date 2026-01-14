#pragma once
#include "shape.h"

class I : public shape {
private:
    int position;

public:
    I();

    void rotate(int arr[20][10]) override;
    void updateCoordinates() override;
};
