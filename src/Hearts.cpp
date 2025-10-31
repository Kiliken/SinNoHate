# include "Hearts.h"

Hearts::Hearts(Vec2 spawnPos, PlayerController* p) {
    collider.center = spawnPos;
    collider.setR(20.0);
    sprite = TextureAsset(U"HeartSprite");

    player = p;
    playerCollider = p->Collider();
}

bool Hearts::Update(){
    const double deltaTime = Scene::DeltaTime();

    collider.center.y -= deltaTime * 100.0;

    if(playerCollider->intersects(collider)){
        
        player->HealLife();
        return true;
    }

    if(collider.center.y < -20.0)
        return true;
    
    return false;
}

void Hearts::Draw(){

    sprite.resized(32).drawAt(collider.center);

}