#pragma once
#include <Siv3D.hpp>

class Enemy {
public:
    Enemy(Vec2 spawnPos, int8_t t, int8_t speedType);
    ~Enemy();

private:
    int8_t enemyType;
    int8_t enemySpeed;

    Texture enemyTexture;
    Vec2 enemyPos;
    Circle enemyCollider;
    double EnemySpeed = 100.0;

    Vec2* playerPos;
    ColorF enemyColor; //just for debug, gonna use shader palette after 



public:

    bool Update();
    void Draw();
};