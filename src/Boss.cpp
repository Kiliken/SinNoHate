# include "Boss.h"


Boss::Boss(PlayerController* p)
{
    // textureAsset constant
    sprite = TextureAsset(U"BossSprite");
    pos = {Scene::Width()/2, Scene::Height() - 50};
    speed = 0;
    player = p;
    playerCollider = p->Collider();

    collider.setR(40.0);

    lustShadowPos = pos;
    lustShadowCollider.setR(40.0);
    
        
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
        if(pos.x < 30.0)
            pos.x = 30.0;

        if(pos.x > Scene::Width() - 30.0)
            pos.x = Scene::Width() - 30.0;

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
        //player->OnDamage();
        damageCooldown = 10.0;
        //Print << U"SHADOW HIT";
    }

    if (switchFase > 0){
        switchFase -= deltaTime;
    }

    if(switchFase <= 0 ){
        curretType = RandomUint8() % 7;
        // Print << curretType;
        if( curretType == 4 )
            lustShadowPos = pos;

        switchFase = 5.0;
    }

    if(pos.y < -5){
        pos.y = 0;
        facing = 2.5;
    }

    if(pos.y > Scene::Height() + 5){
        pos.y = Scene::Height();
        facing = -1.5;
    }

    if (hitTime <= hitDuration)
    {
        hitTime += deltaTime;

        double t = Clamp(hitTime / hitDuration, 0.0, 1.0);
        hitColor = ColorF(Palette::Gray).lerp(ColorF(Palette::White), t);
    }
        

    return false;
}

void Boss::Draw()
{
    const uint64 t = Time::GetMillisec();
	const int32 x = (t / 120 % 5);
    sprite((128 * x),0,128,128).resized(256).drawAt(pos, hitColor); // add color

    if(curretType == 4){
        sprite((128 * x),0,128,128).resized(256).drawAt(lustShadowPos, ColorF(0.7, 0.7,0.7));
    }

    //collider.draw();

}

Circle Boss::GetCollider() { return collider; }

int8_t Boss::GetCurretType() { return curretType; }

bool Boss::GetStatus() { return isAlive; }

void Boss::GetDamage() {
    hp--;
    hitTime = 0.0;

    if(hp < 0)
        isAlive = false; //GAME WON!
}

void Boss::Reset(){
    pos = {Scene::Width()/2, Scene::Height() - 50};
    speed = 0;
    lustShadowPos = pos;
    curretType = 0;
    hp = 50;

    damageCooldown = 0;
    facing = -1.0;
    switchFase = 5.0;
    isAlive = true;

    hitColor = {Palette::White};
    hitDuration = 0.25;
    hitTime = hitDuration;

    
}
