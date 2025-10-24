#include "Enemy.h"

Enemy::Enemy(Vec2 spawnPos, int8_t t, int8_t speedType)
{
    //textureAsset constant
    enemyTexture = TextureAsset(U"EnemyTexture");
    enemyPos = spawnPos;
    enemyType = t;
    enemySpeed = speedType * 10;
    switch (enemyType)
    {
    case 1:
        enemyColor = ColorF(0.5,0,0);
        break;
    
    case 2:
        enemyColor = ColorF(0,0.5,0);
        break;
    case 3:
        enemyColor = ColorF(0,0,0.5);
        break;
    }
}

Enemy::~Enemy()
{

}

void Enemy::Update()
{
    const double deltaTime = Scene::DeltaTime();
    enemyPos.y -= (deltaTime * EnemySpeed);

    if (enemyPos.distanceFrom(*playerPos) <= 20)
    {
        // take damage
    }
}

void Enemy::Draw()
{
    
    enemyTexture.resized(50).drawAt(enemyPos, enemyColor);
}