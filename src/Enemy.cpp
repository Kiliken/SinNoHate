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
    if(enemyType == 4){
        //make the other enemy
        lustShadowPos = enemyPos;
        lustShadowCollider.setR(20.0);
    } 
        
}

Enemy::~Enemy()
{
    
}

bool Enemy::Update()
{
    const double deltaTime = Scene::DeltaTime();
    const double time = Scene::Time();
    
    Vec2 direction = playerCollider->center - enemyPos;
    direction.normalize();
    //Math::Clamp(playerCollider->center.x - enemyPos.x,-1.0,1.0);
    //Enemy movement
    
    
    switch (enemyType)
    {
    case 0:
        //enemyPos.y -= (deltaTime * 100);
        if(enemyPos.distanceFrom(playerCollider->center) > 30.0)
            enemyPos +=  direction * deltaTime * (direction.y < 0 ? 100.0 : 50.0);
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
        enemyPos.x += Math::Sin(time) * deltaTime * 50;
        lustShadowPos.y -= (deltaTime * 100);
        lustShadowPos.x += Math::Sin(time) * deltaTime * -50;
        break;
    case 5:
        enemyPos.x += Math::Sin(time) * deltaTime * 100;
        enemyPos.y += Math::Cos(time) * deltaTime * 100;
        enemyPos.y -= (deltaTime * 50.0);
        break;
    case 6:
        //enemyPos.y -= (deltaTime * 100);
        if(enemyPos.distanceFrom(playerCollider->center) > 30.0)
            enemyPos +=  direction * deltaTime * (direction.y < 0 ? 200.0 : 150.0);
        break;
    }
    

    {
        if(enemyPos.x < 20.0)
            enemyPos.x = 20.0;

        if(enemyPos.x > Scene::Width() - 20.0)
            enemyPos.x = Scene::Width() - 20.0;

    }
    
    enemyCollider.center = enemyPos;
    if(enemyType == 4)
        lustShadowCollider.center = lustShadowPos;


    if (damageCooldown > 0){
        damageCooldown -= deltaTime;
    }

    if (playerCollider->intersects(enemyCollider) && damageCooldown <= 0)
    {
        player->OnDamage();
        damageCooldown = 10.0;
    }

    if (enemyType == 4 && playerCollider->intersects(lustShadowCollider) && damageCooldown <= 0)
    {
        player->OnDamage();
        damageCooldown = 10.0;
        Print << U"SHADOW HIT";
    }


    if(enemyPos.y < -20)
        return true;

    return false;
}

void Enemy::Draw()
{
    const uint64 t = Time::GetMillisec();
	const int32 x = (t / 120 % 5);
    enemyTexture((64 * x),0,64,64).resized(64).drawAt(enemyPos); // add color

    if(enemyType == 4){
        enemyTexture((64 * x),0,64,64).resized(64).drawAt(lustShadowPos, ColorF(0.7, 0.7,0.7));
    }
    //enemyCollider.draw();

}

Circle Enemy::GetCollider() { return enemyCollider; }

int8_t Enemy::GetEnemyType() { return enemyType; }



