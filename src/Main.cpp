#include <Siv3D.hpp> // Siv3D v0.6.16
#include "MapManager.h"
#include "Player/PlayerController.h"
#include "Shop.h"
#include "Enemy.h"
#include "Title.h"

struct PaletteSettings
{
    unsigned int currentPalette;
};

void Main()
{

    // Create a window
    Window::SetTitle(U"罪の果て");
    Window::Resize(512, 480);

    const PixelShader paletteSwap = HLSL{U"Assets/shaders/colorSwap.hlsl", U"PS_PaletteSwap"};
    const ScopedRenderStates2D sampler{SamplerState::ClampNearest};

    ConstantBuffer<PaletteSettings> enemyPalette[7];
    ConstantBuffer<PaletteSettings> stagePalette[8];

    for (int i = 0; i < 7; i++)
    {
        enemyPalette[i]->currentPalette = static_cast<unsigned int>(i);
        stagePalette[i]->currentPalette = static_cast<unsigned int>(i);
    }
    stagePalette[7]->currentPalette = static_cast<unsigned int>(7);

    const Texture enemyPaletteTexture(U"Assets/EnemyPalette.png");
    const Texture stagePaletteTexture(U"Assets/StagePalette.png");

    // Load textures and sprites
    // Texture mapTexture(U"map.png");
    TextureAsset::Register(U"MapTexture", U"Assets/MapTexture.png");
    TextureAsset::Register(U"EnemySprite", U"Assets/EnemySprite.png");
    TextureAsset::Register(U"PlayerSprite", U"Assets/PlayerSprite.png");
    // Load font
    FontAsset::Register(U"Text", FontMethod::MSDF, 48, U"Assets/DotGothic16-Regular.ttf");

    Array<Enemy> enemies;
    constexpr double InitialEnemySpawnInterval = 2.0;
    double enemySpawnTime = InitialEnemySpawnInterval;
    double enemyAccumulatedTime = 0.0;

    Map map;                                             // Create map instance
    Shop shop;                                           // Create shop instance
    PlayerController playerController({256.0f, 240.0f}); // Create player controller instance
    Title title;

    while (System::Update())
    {
        if (!title.gameStarted)
        {
            title.update();
            //title.draw();
            continue;
        }


        const double deltaTime = Scene::DeltaTime();
        enemyAccumulatedTime += deltaTime;

        while (enemySpawnTime <= enemyAccumulatedTime && map.currentLayer < map.layerCount - 1)
        {
            enemyAccumulatedTime -= enemySpawnTime;
            // enemySpawnTime = Max(enemySpawnTime * 0.95, 0.3);
            // enemies << GenerateEnemy();
            enemies << Enemy(RandomUint8() % (map.currentLayer + 1), &playerController);
        }

        // debug
        if (KeyE.down())
        {
            // map.GoToNextLayer();
            // shop.ResetShop();
            // shop.ShowShop();

            // map.ResetMap();
            enemies.clear();
            map.MapGameClear();
        }

        // handle layer switching and shop
        if (map.layerSwitched)
        {
            enemies.clear();
            // up to final boss
            if (map.currentLayer <= map.layerCount)
            {
                // wait for player to finish shopping
                if (!shop.shopActive)
                    shop.ShowShop();

                shop.UpdateShop(playerController);

                if (shop.itemBought)
                {
                    map.StartNextLayer();
                    shop.ResetShop();

                    enemySpawnTime -= 0.4; // change the enemey spawn count based on the level
                    enemySpawnTime = Math::Max(enemySpawnTime, 0.3);
                }
            }
            // game clear
            else if (map.allLayersCleared)
            {
                enemies.clear();
                map.MapGameClear();
            }
        }

        map.UpdateMap(deltaTime, playerController, &enemies);
        // shop.UpdateShop(player); // update shop

        // when player is inactive
        if (map.layerSwitched)
        {
            playerController.Update(deltaTime, false);
        }
        else
        {
            playerController.Update(deltaTime, true);
        }

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
                    // spawn heart on 10%
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
        {
            
            Graphics2D::SetPSTexture(1, stagePaletteTexture);
            const ScopedCustomShader2D shader{paletteSwap};
            Graphics2D::SetPSConstantBuffer(1, stagePalette[map.currentLayer]);

            map.Draw();
        }

        // RESET SHADER HERE
        playerController.Draw(deltaTime);
        shop.DrawShop();

        {

            // Draw the enemies
            Graphics2D::SetPSTexture(1, enemyPaletteTexture);
            const ScopedCustomShader2D shader{paletteSwap}; // enemy shader palette

            for (auto &enemy : enemies)
            {
                Graphics2D::SetPSConstantBuffer(1, enemyPalette[enemy.GetEnemyType()]);
                enemy.Draw();
            }

            Graphics2D::SetPSConstantBuffer(1, enemyPalette[enemy.GetEnemyType()]);
            enemy.Draw();
        } 

        if (title.gameStarted && title.startingSeqCounter > 0 && title.startingSeqCounter < 4) {
            title.update();

        }
    }
}