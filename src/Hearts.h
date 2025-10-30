# pragma once
# include <Siv3D.hpp>
# include "Player/PlayerController.h"

class Hearts {
public:
    Hearts(Vec2 spawnPos, PlayerController* p);
    ~Hearts() {}

private:
    Circle collider;
    Texture sprite;

    PlayerController* player;
    Circle* playerCollider;

public:
    bool Update();
    void Draw();
};