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

BulletBase::BulletBase(Vec2 firstPosition, Vec2 firstDirection, int radius)
{
    m_isActive = true;
    m_position = firstPosition;
    m_sprite = Circle{ m_position, radius };
    m_moveDirection = firstDirection;
    m_color = Palette::Red;
}

void BulletBase::Init(Vec2 firstPosition, Vec2 firstDirection, int radius)
{
    m_isActive = true;
    m_position = firstPosition;
    m_sprite = Circle{ m_position, radius };
    m_moveDirection = firstDirection;
}

void BulletBase::Update(double deltaTime)
{
    if (!m_isActive) return;
    UpdateVelocity();
    m_position += m_velocity * deltaTime;
    if (0 > m_position.x || m_position.x > Scene::Width()) m_isActive = false;
    if (0 > m_position.y || m_position.y > Scene::Height()) m_isActive = false;
}

void BulletBase::Draw()
{
    if (!m_isActive) return;
    m_sprite.setPos(m_position);
    m_sprite.draw(m_color);
}

void BulletBase::OnHit()
{
    m_isActive = false;
}
