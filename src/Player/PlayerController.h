#pragma once

#include <Siv3D.hpp>
#include "Bullet/BulletBase.h"

class PlayerController{
    private:
        const double m_moveForce = 300.0;		// 移動速度1秒あたり
        const double m_jumpForce = 300.0;		// ジャンプ初速度
        const double m_gravity = -0.98;
        const double m_gravityScale = 500.0;
        const double m_shootPosDistance = 50.0;
        Vec2 m_velocity{ 0, 0 };				// 現在の移動速度
        Vec2 m_position{ 0, 0 };				// 現在の座標
        Texture m_crossHair;
        Vec2 m_shotPos{ 0, 0 };
        Vec2 m_aimDirection{ 0, 0 };
        double m_aimAngle = 0;

        Texture m_sprite;				// プレイヤーの見た目のテクスチャ
        Circle m_collider;
        Vec2 m_firstPosition;			// 初期位置
        int m_maxLife = 3;				// 最大ライフ
        int m_life = m_maxLife;					// 現在のライフ
        int m_bulletRadius = 10;        // 弾の大きさ
        double m_shotCoolTime = 0.5;			// ショットのクールダウン時間：秒
        double m_shotCoolDown = m_shotCoolTime;				// ショットのクールタイム
        bool m_inFinalLayer = false;
        bool m_shotable = true;
        Array<BulletBase*> m_bullets;

        /// @brief マウスカーソルの位置に応じて発射方向を管理
        void Aiming();

        /// @brief 発射したすべての弾を管理する
        /// @param deltaTime 微小時間
        void UpdateBullets(double deltaTime);

        /// @brief ショットのクールタイムを管理する
        /// @param deltaTime 微小時間
        void UpdateShotCoolTime(double deltaTime);

        /// @brief 入力に応じて現在の速度を更新した値を返す
        /// @param velocity 現在の移動速度
        void UpdateVelocity(Vec2 velocity);

        /// @brief 移動速度に応じて、プレイヤーオブジェクトを移動させる
        /// @param velocity 現在の移動速度
        /// @param deltaTime 微小時間
        void Move(Vec2 velocity, double deltaTime);

        /// @brief 入力があれば処理を行う
        void Jump();

        /// @brief 入力があれば弾を打つ
        void Shot();

        /// @brief Y座標が初期位置より上であれば、重力による速度の更新を行う
        /// @param deltaTime 微小時間
        void UpdateVelocityYByGravity(double deltaTime);

        /// @brief ライフの値を更新する
        /// @param addValue 加算値
        void UpdateLife(int addValue);

    public:
        /// @brief プレイヤーの移動管理クラス
        /// @param firstPosition 初期位置
        PlayerController(Vec2 firstPosition);

        ~PlayerController() noexcept ;

        /// @brief ダメージを受けた時の処理
        void OnDamage();

        /// @brief ライフ回復処理
        void HealLife();

        /// @brief 最大ライフを増加させる
        /// @param addValue 加算値
        void UpGrade_IncreaseMaxLife(int addValue);

        /// @brief 弾のサイズを大きくする
        /// @param expansValue 加算値
        void UpGrade_ExpansionBullet(int expansValue);

        /// @brief 移動速度を上げる
        /// @param subtractValue 加算値
        void UpGrade_DecreaseAttackSpan(double subtractValue);

        /// @brief 現在のライフを取得
        int Life() const { return m_life; }

        /// @brief 最大ライフを取得
        int MaxLife() const { return m_maxLife; }

        /// @brief 各状態の更新処理
        /// @param deltaTime 微小時間
        void Update(double deltaTime);

        /// @brief 描画処置
        /// @param deltaTime 微小時間
        void Draw(double deltaTime);

        void OnFinalLayer();

        /// @brief 当たり判定を取得
        Circle* Collider();

        /// @brief 弾の配列を取得
        Array<BulletBase*>& GetBullets() { return m_bullets; }
};