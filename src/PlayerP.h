// placeholder player class
#pragma once
#include <Siv3D.hpp>

class Player {
public:
    int width = 32;
    int height = 32;
    int maxHP = 10;
    int currentHP = 10;
    Point position = {0, 0};
    Rect collider = Rect(position.x, position.y, width, height);
};