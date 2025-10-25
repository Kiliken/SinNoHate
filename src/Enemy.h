#pragma once
#include <Siv3D.hpp>
#include "Player/PlayerController.h"

class Enemy {
public:
    Enemy(int8_t t, PlayerController* p);
    ~Enemy();

private:
    int8_t enemyType;
    int8_t enemySpeed;

    Texture enemyTexture;
    Vec2 enemyPos;
    Circle enemyCollider;
    double EnemySpeed = 100.0;
    double damageCooldown = 0;

    PlayerController* player;
    Circle* playerCollider;

public:

    bool Update();
    void Draw();
    Circle GetCollider();

    int8_t GetEnemyType();
};