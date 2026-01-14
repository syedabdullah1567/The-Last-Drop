#pragma once
#include "shape.h"

class O : public shape {
private:
    int position;

public:
    O();

    void rotate(int arr[20][10]) override;
    void updateCoordinates() override;
};
