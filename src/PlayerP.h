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

    struct Bullet {
        Vec2 position;
        Vec2 velocity;
        int damage;
        Rect collider;

        Bullet(Vec2 pos, Vec2 vel, int dmg)
            : position(pos), velocity(vel), damage(dmg),
              collider(pos.x, pos.y, 8, 8) {}
    };

    Array<Bullet> bullets;
};