#include <Siv3D.hpp> // Siv3D v0.6.16
#include "MapManager.h"
#include "Player/PlayerController.h"
#include "Shop.h"
#include "Enemy.h"

void Main()
{

    // Create a window
    Window::SetTitle(U"罪の果て");
    Window::Resize(512, 480);

    const PixelShader paletteSwap = HLSL{ U"Assets/shaders/colorSwap.hlsl", U"PS_PaletteSwap" };
    const ScopedRenderStates2D sampler{ SamplerState::ClampNearest };

    

    // Load map texture
    Texture mapTexture(U"map.png");
    TextureAsset::Register(U"EnemySprite", U"Assets/EnemySprite.png");
    TextureAsset::Register(U"PlayerSprite", U"Assets/PlayerSprite.png");

    Array<Enemy> enemies;
    constexpr double InitialEnemySpawnInterval = 2.0;
    double enemySpawnTime = InitialEnemySpawnInterval;
    double enemyAccumulatedTime = 0.0;

    Map map;                                             // Create map instance
    Shop shop;                                           // Create shop instance
    PlayerController playerController({256.0f, 240.0f}); // Create player controller instance

    while (System::Update())
    {
        const double deltaTime = Scene::DeltaTime();
        enemyAccumulatedTime += deltaTime;

        while (enemySpawnTime <= enemyAccumulatedTime)
        {
            enemyAccumulatedTime -= enemySpawnTime;
            enemySpawnTime = Max(enemySpawnTime * 0.95, 0.3);
            // enemies << GenerateEnemy();
            enemies << Enemy(RandomUint8() % 4, RandomUint8() % 4, &playerController);
        }

        // debug
        if (KeyE.down())
        {
            // map.GoToNextLayer();
            shop.ResetShop();
            shop.ShowShop();
        }

        // handle layer switching and shop
        if (map.layerSwitched)
        {
            // wait for player to finish shopping
            if (!shop.shopActive)
                shop.ShowShop();

            shop.UpdateShop(playerController);

            if (shop.itemBought)
            {
                map.StartNextLayer();
                shop.ResetShop();
            }
        }

        map.UpdateMap(deltaTime, playerController, &enemies);
        // shop.UpdateShop(player); // update shop
        playerController.Update(deltaTime);

        // EnemyLoop
        for (auto enemy = enemies.begin(); enemy != enemies.end();)
        {
            if (enemy->Update())
            {
                enemy = enemies.erase(enemy);
                continue;
            }

            bool erased = false;
            for (const auto &bullet : playerController.GetBullets())
            {
                if (bullet->GetCollider()->intersects(enemy->GetCollider()))
                {
                    bullet->OnHit();
                    enemy = enemies.erase(enemy);
                    erased = true;
                    break;
                }
            }

            if (!erased)
                ++enemy;
        }

        
        // Draw the map
        
        map.Draw(mapTexture);
        playerController.Draw(deltaTime);
        shop.DrawShop();

        // Draw the enemies

        const ScopedCustomShader2D shader{ paletteSwap }; // enemy shader palette
        for (auto &enemy : enemies)
        {
            enemy.Draw();
        }
    }
}
