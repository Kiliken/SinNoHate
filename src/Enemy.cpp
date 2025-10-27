#include "Enemy.h"



Enemy::Enemy(int8_t t, PlayerController* p)
{
    // textureAsset constant
    enemyTexture = TextureAsset(U"EnemySprite");
    enemyPos = RandomVec2({ 20, Scene::Width() - 20 }, Scene::Height() + 20);
    enemyType = t;
    enemySpeed = t * 10;
    player = p;
    playerCollider = p->Collider();

    enemyCollider.setR(20.0);

    // Lust
    if(enemyType == 5){
        //make the other enemy
    } 
        
}

Enemy::~Enemy()
{
    
}

bool Enemy::Update()
{
    const double deltaTime = Scene::DeltaTime();
    const double time = Scene::Time();
    
    const double directionX = (playerCollider->center.y <= enemyPos.y ? 
        (Math::Abs(playerCollider->center.x - enemyPos.x)  > 20.0 ? 
            Math::Clamp(playerCollider->center.x - enemyPos.x, -1.0, 1.0) : 0.0) : 0.0);
    
    Vec2 direction = playerCollider->center - enemyPos;
    
    //Math::Clamp(playerCollider->center.x - enemyPos.x,-1.0,1.0);
    //Enemy movement
    
    
    switch (enemyType)
    {
    case 0:
        enemyPos.y -= (deltaTime * 100);
        enemyPos += direction.normalized() * deltaTime * 50.0;
        break;
    case 1:
        enemyPos.y -= (deltaTime * 100);
        enemyPos.x += Math::Sin(time) * deltaTime * 50;
        break;
    case 2:
        enemyPos.x += Math::Sin(time) * deltaTime * 50;
        enemyPos.y -= ( Math::Abs(Math::Sin(time)) > 0.5 ?  deltaTime * 100 : deltaTime * -25 );
        break;
    case 3:
        enemyPos.x +=  ( Math::Abs(Math::Cos(time)) > 0.5 ?  deltaTime * Math::Sin(time) * 100 : 0 );
        enemyPos.y -= ( Math::Abs(Math::Cos(time)) < 0.5 ?  deltaTime * 100 : deltaTime * 25 );
        break;
    case 4:
        enemyPos.y -= (deltaTime * 100);
        break;
    case 5:
        enemyPos.x += Math::Sin(time) * deltaTime * 100;
        enemyPos.y += Math::Cos(time) * deltaTime * 100;
        enemyPos.y -= (deltaTime * 50.0);
        break;
    case 6:
        enemyPos.y -= (deltaTime * 100);
        enemyPos += direction.normalized() * deltaTime * 100.0;
        break;
    }
   
    
    
    
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

int8_t Enemy::GetEnemyType() { return enemyType; }



