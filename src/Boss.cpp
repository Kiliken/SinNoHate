# include "Boss.h"


Boss::Boss(PlayerController* p)
{
    // textureAsset constant
    sprite = TextureAsset(U"EnemySprite");
    pos = RandomVec2({ 20, Scene::Width() - 20 }, Scene::Height() + 20);
    speed = 0;
    player = p;
    playerCollider = p->Collider();

    collider.setR(20.0);

    lustShadowPos = pos;
    lustShadowCollider.setR(20.0);
    
        
}

Boss::~Boss()
{
    
}

bool Boss::Update()
{
    const double deltaTime = Scene::DeltaTime();
    const double time = Scene::Time();
    
    Vec2 direction = playerCollider->center - pos;
    direction.normalize();
    //Math::Clamp(playerCollider->center.x - enemyPos.x,-1.0,1.0);
    //Enemy movement
    
    
    switch (curretType)
    {
    case 0:
        //enemyPos.y -= (deltaTime * 100);
        pos +=  direction * deltaTime * (direction.y < 0 ? 100.0 : 50.0);
        break;
    case 1:
        pos.y += (deltaTime * 100) * facing;
        pos.x += Math::Sin(time) * deltaTime * 50;
        break;
    case 2:
        pos.x += Math::Sin(time) * deltaTime * 50;
        pos.y += ( Math::Abs(Math::Sin(time)) > 0.5 ?  deltaTime * 100 * facing : deltaTime * -25 * facing );
        break;
    case 3:
        pos.x +=  ( Math::Abs(Math::Cos(time)) > 0.5 ?  deltaTime * Math::Sin(time) * 100 : 0 );
        pos.y += ( Math::Abs(Math::Cos(time)) < 0.5 ?  deltaTime * 100 * facing : deltaTime * 25 * facing );
        break;
    case 4:
        pos.y += (deltaTime * 100) * facing;
        pos.x += Math::Sin(time) * deltaTime * 50;
        lustShadowPos.y += (deltaTime * 100) * facing;
        lustShadowPos.x += Math::Sin(time) * deltaTime * -50;
        break;
    case 5:
        pos.x += Math::Sin(time) * deltaTime * 100;
        pos.y += Math::Cos(time) * deltaTime * 100;
        pos.y += (deltaTime * 50.0) * facing;
        break;
    case 6:
        //enemyPos.y -= (deltaTime * 100);
        pos +=  direction * deltaTime * (direction.y < 0 ? 200.0 : 150.0);
        break;
    }
    

    {
        if(pos.x < 20.0)
            pos.x = 20.0;

        if(pos.x > Scene::Width() - 20.0)
            pos.x = Scene::Width() - 20.0;

    }
    
    collider.center = pos;
    if(curretType == 4)
        lustShadowCollider.center = lustShadowPos;


    if (damageCooldown > 0){
        damageCooldown -= deltaTime;
    }

    if (playerCollider->intersects(collider) && damageCooldown <= 0)
    {
        player->OnDamage();
        damageCooldown = 10.0;
    }

    if (curretType == 4 && playerCollider->intersects(lustShadowCollider) && damageCooldown <= 0)
    {
        player->OnDamage();
        damageCooldown = 10.0;
        Print << U"SHADOW HIT";
    }

    if (switchFase > 0){
        switchFase -= deltaTime;
    }

    if(switchFase <= 0 ){
        curretType = RandomInt32() % 7;
        switchFase = 30.0;
    }

    if(pos.y < -20){
        pos.y = -15;
        facing = 1.0;
    }

    if(pos.y > Scene::Height() + 20){
        pos.y > Scene::Height() + 15;
        facing = -1.0;
    }
        

    return false;
}

void Boss::Draw()
{
    const uint64 t = Time::GetMillisec();
	const int32 x = (t / 120 % 5);
    sprite((32 * x),0,32,32).resized(128).drawAt(pos); // add color

    if(curretType == 4){
        sprite((32 * x),0,32,32).resized(128).drawAt(lustShadowPos, ColorF(0.7, 0.7,0.7));
    }
    //enemyCollider.draw();

}

Circle Boss::GetCollider() { return collider; }

int8_t Boss::GetEnemyType() { return curretType; }
