#pragma once
#include <Siv3D.hpp>
#include "Player/PlayerController.h"

class Enemy {
public:
    Enemy(int8_t t, int8_t speedType, PlayerController* p);
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

    ColorF enemyColor; //just for debug, gonna use shader palette after 



public:

    bool Update();
    void Draw();
    Circle GetCollider();
};