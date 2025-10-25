#pragma once

#include <Siv3D.hpp>

class BulletBase{
    protected:
        const double m_moveSpeed = 500.0;	// 移動速度
        Circle m_sprite;		// テクスチャ
        Vec2 m_velocity{ 0, 0 };

        Color m_color;
        Vec2 m_moveDirection;
        Vec2 m_position;

        bool m_isActive;

        virtual void UpdateVelocity();

    public:
        bool IsActive();

        BulletBase(Vec2 firstPosition, Vec2 firstDirection, int radius);

        void Init(Vec2 firstPosition, Vec2 firstDirection, int radius);

        void Update(double deltaTime);

        void Draw();

        void OnHit();

        Circle* GetCollider() { return &m_sprite; }
};