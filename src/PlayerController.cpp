#include "Player/PlayerController.h"

void PlayerController::Aiming()
{
    Vec2 cursorPos = Cursor::PosF();
    m_aimDirection = (cursorPos - m_position).normalized();
    m_shootPos.setPos(m_position + (m_aimDirection * m_shootPosDistance));
}

void PlayerController::UpdateBullets(double deltaTime)
{
    if (m_bullets.isEmpty()) return;

    for (auto& bullet : m_bullets){
        bullet->Update(deltaTime);
        bullet->Draw();
    }
}

void PlayerController::UpdateShotCoolTime(double deltaTime)
{
    if (m_shotable) return;

    m_shotCoolDown -= deltaTime;
    if (m_shotCoolDown < 0){
        m_shotCoolDown = m_shotCoolTime;
        m_shotable = true;
    }
}

void PlayerController::UpdateVelocity(Vec2 velocity)
{
    // 入力に応じて左右移動速度を更新する
    if (KeyD.pressed() && KeyA.pressed()){
        m_velocity.x = 0 * m_moveForce;
    }
    else if (!KeyD.pressed() && !KeyA.pressed()){
        m_velocity.x = 0 * m_moveForce;
    }
    else if (KeyD.pressed()){
        m_velocity.x = 1 * m_moveForce;
    }
    else if (KeyA.pressed()){
        m_velocity.x = -1 * m_moveForce;
    }

    // 上下移動速度も更新
    if (m_moveableVertical){
        if (KeyW.pressed() && KeyS.pressed()){
            m_velocity.y = 0 * m_moveForce;
        }
        else if (!KeyW.pressed() && !KeyS.pressed()){
            m_velocity.y = 0 * m_moveForce;
        }
        else if (KeyW.pressed()){
            m_velocity.y = 1 * m_moveForce;
        }
        else if (KeyS.pressed()){
            m_velocity.y = -1 * m_moveForce;
        }
    }
}

void PlayerController::Move(Vec2 velocity, double deltaTime)
{
    velocity.y *= -1;
    m_position += velocity * deltaTime;
    m_position.x = Clamp(m_position.x, 0.0, (double)Scene::Width());
    m_position.y = Clamp(m_position.y, 0.0, (double)Scene::Height());
}

void PlayerController::Jump()
{
    if (KeySpace.down()){
        m_velocity.y = m_jumpForce;
    }
}

void PlayerController::Shot()
{
    if (!m_shotable) return;
    if (MouseL.down()){
        // すでに発射済みで非アクティブ化している球がある場合それを再利用
        if (!m_bullets.isEmpty()){
            for (auto& bullet : m_bullets){
                if (!bullet->IsActive()){
                    bullet->Init(m_shootPos.center, m_aimDirection);
                    m_shotable = false;
                    return;
                }
            }
        }
        // ない場合、新たに生成
        BulletBase* bullet = new BulletBase{ m_shootPos.center, m_aimDirection };
        m_shotable = false;
        m_bullets << bullet;
    }
}

void PlayerController::UpdateVelocityYByGravity(double deltaTime)
{
    // 初期位置まで行けば速度とY座標をリセット
    if (m_position.y > m_firstPosition.y){
        m_velocity.y = 0;
        m_position.y = m_firstPosition.y;
        return;
    }

    m_velocity.y += m_gravity * m_gravityScale * deltaTime;
}

PlayerController::PlayerController(Vec2 firstPosition)
{
    m_firstPosition = firstPosition;
    m_position = m_firstPosition;
    m_sprite = Texture{ U"😇"_emoji };
    m_collider = Circle{ m_position, m_sprite.size() };
}

PlayerController::~PlayerController() noexcept
{
    // 生成したすべての球を破棄する
    for (auto& bullet : m_bullets){
        delete bullet;
    }
}

void PlayerController::OnDamage()
{
    UpdateLife(-1);
}

void PlayerController::HealLife()
{
    UpdateLife(1);
}

void PlayerController::UpdateLife(int addValue)
{
    m_life += addValue;
    m_life = Clamp(m_life, 0, m_maxLife);
}

void PlayerController::Update(double deltaTime)
{
    Aiming();
    Shot();
    UpdateBullets(deltaTime);
    UpdateShotCoolTime(deltaTime);
    UpdateVelocity(m_velocity);
    Move(m_velocity, deltaTime);
    m_collider.setPos(m_position);
}

void PlayerController::Draw(double deltaTime)
{
    m_collider.scaled(0.2).draw(Palette::Red);
    m_sprite.drawAt( m_position );
    m_shootPos.draw(Palette::Aqua);
}

void PlayerController::OnLastLayer()
{
    m_moveableVertical = true;
}

Circle *PlayerController::Collider()
{
    return &m_collider;
}
