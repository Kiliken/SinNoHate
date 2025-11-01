#pragma once

#include <Siv3D.hpp>

class BulletBase{
    protected:
        const double m_moveSpeed = 500.0;	// 移動速度
        const int m_swapSpriteLayerID = 3;      // 弾の見た目が変わるレイヤー番号
        Texture m_sprite;		// テクスチャ
        Circle m_collider;      // 当たり判定
        Vec2 m_velocity{ 0, 0 };

        Color m_color;
        double m_radius;
        Vec2 m_moveDirection;
        Vec2 m_position;

        bool m_isActive;

        virtual void UpdateVelocity();

    public:
        bool IsActive();

        BulletBase(Vec2 firstPosition, Vec2 firstDirection, double radius, int layerIndex);

        void Init(Vec2 firstPosition, Vec2 firstDirection, int radius);

        void Update(double deltaTime);

        void Draw();

        void OnHit();

        Circle* GetCollider() { return &m_collider; }
};