#include <Siv3D.hpp>
#include "Bullet/BulletBase.h"

void BulletBase::UpdateVelocity()
{
    m_velocity = m_moveDirection.normalized() * m_moveSpeed;
}

bool BulletBase::IsActive()
{
    return m_isActive;
}

BulletBase::BulletBase(Vec2 firstPosition, Vec2 firstDirection, double radius, int layerIndex, int penetration)
{
    m_isActive = true;
    m_position = firstPosition;
    m_radius = radius;
    if (layerIndex < m_swapSpriteLayerID)
        m_sprite = Texture{ TextureAsset{U"ShotSprite"} };
    else
        m_sprite = Texture{ TextureAsset{U"ShotSpriteEx"} };
    m_collider = Circle{ m_position, m_radius };
    m_moveDirection = firstDirection;
    m_color = Palette::Red;
    m_penetration = penetration;
}

void BulletBase::Init(Vec2 firstPosition, Vec2 firstDirection, int radius)
{
    m_isActive = true;
    m_position = firstPosition;
    m_radius = radius;
    m_collider = Circle{ m_position, m_radius };
    m_moveDirection = firstDirection;
}

void BulletBase::Update(double deltaTime)
{
    if (!m_isActive) return;
    UpdateVelocity();
    m_position += m_velocity * deltaTime;
    m_collider.setPos(m_position);
    if (0 > m_position.x || m_position.x > Scene::Width()) m_isActive = false;
    if (0 > m_position.y || m_position.y > Scene::Height()) m_isActive = false;
}

void BulletBase::Draw()
{
    if (!m_isActive) return;
    const uint64 t = Time::GetMillisec();
    const int32 x = (t / 60 % 3);
    const double angle = Math::Atan2(m_moveDirection.normalized().x * -1, m_moveDirection.normalized().y);
    m_sprite((64 * x),0,64,64).resized(m_radius / 10 * 64).rotated(angle).drawAt(m_position);
}

void BulletBase::OnHit(bool isBoss)
{
    if (isBoss) {
        m_penetration = 0;
    } else {
        m_penetration --;
    }
    
    if (m_penetration <= 0) {
        m_isActive = false;
    }
    
}
