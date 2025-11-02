# include <Siv3D.hpp>
#include "Player/PlayerController.h"

class Boss {
public:
    Boss(PlayerController* p);
    ~Boss();

private:
    int8_t curretType;
    int8_t hp = 50;

    Texture sprite;
    Vec2 pos;
    Circle collider;
    double speed = 100.0;
    double damageCooldown = 0;
    double facing = -1.0;
    double switchFase = 5.0;
    bool isAlive = true;

    Color hitColor = {Palette::White};
    double hitDuration = 0.25;
    double hitTime = hitDuration;

    Vec2 lustShadowPos;
    Circle lustShadowCollider;

    PlayerController* player;
    Circle* playerCollider;

    
public:

    bool Update();
    void Draw();
    Circle GetCollider();

    int8_t GetCurretType();
    bool GetStatus();
    void GetDamage();

    void Reset();
};