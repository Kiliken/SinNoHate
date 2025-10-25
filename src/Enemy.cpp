#include "Enemy.h"



Enemy::Enemy(int8_t t, int8_t speedType, PlayerController* p)
{
    // textureAsset constant
    enemyTexture = TextureAsset(U"EnemySprite");
    enemyPos = RandomVec2({ 20, Scene::Width() - 20 }, Scene::Height() + 20);
    enemyType = t;
    enemySpeed = speedType * 10;
    player = p;
    playerCollider = p->Collider();

    enemyCollider.setR(20.0);

    switch (enemyType)
    {
    case 1:
        enemyColor = ColorF(1, 0.7, 0.7);
        break;

    case 2:
        enemyColor = ColorF(0.7, 1, 0.7);
        break;
    case 3:
        enemyColor = ColorF(0.7, 0.7, 1);
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
    enemyCollider.center = enemyPos;

    if (damageCooldown > 0){
        damageCooldown -= deltaTime;
    }

    if (playerCollider->intersects(enemyCollider) && damageCooldown <= 0)
    {
        player->OnDamage();
        damageCooldown = 10.0;
    }


    if(enemyPos.y < -20)
        return true;

    return false;
}

void Enemy::Draw()
{
    const uint64 t = Time::GetMillisec();
	const int32 x = (t / 120 % 5);
    enemyTexture((32 * x),0,32,32).resized(64).drawAt(enemyPos); // add color

    //enemyCollider.draw();

}

Circle Enemy::GetCollider() { return enemyCollider; }




