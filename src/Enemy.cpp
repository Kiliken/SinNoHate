#include "Enemy.h"

Enemy::Enemy(Vec2 spawnPos, int8_t t, int8_t speedType, Vec2* pPos)
{
    // textureAsset constant
    enemyTexture = TextureAsset(U"EnemyTexture");
    enemyPos = spawnPos;
    enemyType = t;
    enemySpeed = speedType * 10;
    playerPos = pPos;

    switch (enemyType)
    {
    case 1:
        enemyColor = ColorF(0.5, 0, 0);
        break;

    case 2:
        enemyColor = ColorF(0, 0.5, 0);
        break;
    case 3:
        enemyColor = ColorF(0, 0, 0.5);
        break;
    }
}

Enemy::~Enemy()
{
    
}

bool Enemy::Update()
{
    const double deltaTime = Scene::DeltaTime();
    enemyPos.y -= (deltaTime * EnemySpeed);

    if (enemyPos.distanceFrom(*playerPos) <= 40)
    {
        //player takes damage
    }


    if(enemyPos.y < -20)
        return true;

    return false;
}

void Enemy::Draw()
{

    enemyTexture.resized(50).drawAt(enemyPos, enemyColor);
}



