#include "utils.h"


void Main()
{

    // Create a window
    Window::SetTitle(U"罪の果て");
    Window::Resize(512, 480);

    const PixelShader paletteSwap = HLSL{Resource(U"Assets/shaders/colorSwap.hlsl"), U"PS_PaletteSwap"};
    const ScopedRenderStates2D sampler{SamplerState::ClampNearest};

    ConstantBuffer<PaletteSettings> enemyPalette[7];
    ConstantBuffer<PaletteSettings> stagePalette[8];

    for (int i = 0; i < 7; i++)
    {
        enemyPalette[i]->currentPalette = static_cast<unsigned int>(i);
        stagePalette[i]->currentPalette = static_cast<unsigned int>(i);
    }
    stagePalette[7]->currentPalette = static_cast<unsigned int>(7);

    const Texture enemyPaletteTexture(Resource(U"Assets/EnemyPalette.png"));
    const Texture stagePaletteTexture(Resource(U"Assets/StagePalette.png"));

    Effect effect;

    // Load textures and sprites
    // Texture mapTexture(U"map.png");
    TextureAsset::Register(U"MapTexture", Resource(U"Assets/MapTexture.png"));
    TextureAsset::Register(U"TrapTexture", Resource(U"Assets/TrapTexture.png"));
    TextureAsset::Register(U"EnemySprite", Resource(U"Assets/EnemySprite.png"));
    TextureAsset::Register(U"PlayerSprite", Resource(U"Assets/PlayerSprite.png"));
    TextureAsset::Register(U"HeartSprite", Resource(U"Assets/heartSprite.png"));
    TextureAsset::Register(U"BossSprite", Resource(U"Assets/bossSprite.png"));
    TextureAsset::Register(U"HeartTexture", Resource(U"Assets/HeartTexture.png"));    // UI
    TextureAsset::Register(U"ShopTexture", Resource(U"Assets/ShopTexture.png"));
    TextureAsset::Register(U"ShotSprite", Resource(U"Assets/shotSprite.png"));
    TextureAsset::Register(U"ShotSpriteEx", Resource(U"Assets/shotSprite_ex.png"));
    
    // Load Audio
    AudioAsset::Register(U"BGM", Audio::Stream, Resource(U"Assets/sound/lisztInferno.mp3"));
    AudioAsset::Register(U"TitleBGM", Audio::Stream, Resource(U"Assets/sound/lacrimosa.mp3"));
    AudioAsset::Register(U"EndBGM", Audio::Stream, Resource(U"Assets/sound/odetojoy.mp3"));
    

    // Load SFX
    AudioAsset::Register(U"ShootSFX", Audio::Stream, Resource(U"Assets/sound/shoot.mp3"));
    AudioAsset::Register(U"TakeDamageSFX", Audio::Stream, Resource(U"Assets/sound/takedamage.mp3"));
    AudioAsset::Register(U"LevelCardSFX", Audio::Stream, Resource(U"Assets/sound/levelcard.mp3"));
    
    // Load font
    FontAsset::Register(U"Text", FontMethod::MSDF, 48, Resource(U"Assets/DotGothic16-Regular.ttf"));

    Array<Enemy> enemies;
    Array<Hearts> hearts;
    constexpr double InitialEnemySpawnInterval = 2.0;
    double enemySpawnTime = InitialEnemySpawnInterval;
    double enemyAccumulatedTime = 0.0;
    int enemyScore = 100;
    int bossScore = 1000;
    bool gameStart = false;
    bool firstLevelStart = false;

    int currentScore = 0;   // UI
    bool gameClear = false;

    Map map;                                             // Create map instance
    Shop shop;                                           // Create shop instance
    PlayerController playerController({256.0f, 240.0f}, &effect); // Create player controller instance
    Title title;
    UI playerUI;
    LevelTitle levelTitle;
    GameOver gameOver;
    GameClear gameClearSeq;

    Boss boss(&playerController);

    const Audio enemySound{GMInstrument::StringEnsemble1, PianoKey::C1, 0.3s};
    const Audio bgMusic{ AudioAsset{U"BGM"} };
    const Audio titleMusic{ AudioAsset{U"TitleBGM"} };
    const Audio endMusic{ AudioAsset{U"EndBGM"} };

    
    while (System::Update())
    {
        if(gameOver.gameOver){
            if(bgMusic.isPlaying())
                bgMusic.stop();
            
            //gameOver.update();

            // GAME OVER GAME RESET
            if(gameOver.menuBtnPressed){
                map.ResetMap();
                enemies.clear();
                enemySpawnTime = InitialEnemySpawnInterval;
                enemyAccumulatedTime = 0.0;
                hearts.clear();
                boss.Reset();
                playerController.ResetPlayer();
                title.reset();
                gameClear = false;

                gameStart = false;
                firstLevelStart = false;
                levelTitle.level = 0;

                currentScore = 0;

                gameOver.OnMenuBtnPress();
            }
        }

        if (gameClearSeq.gameClear){
            if(bgMusic.isPlaying())
                bgMusic.stop();
            if(!endMusic.isPlaying())
                endMusic.play();

            // gameClearSeq.update();
            if (gameClearSeq.endingSeqCounter >= 26.0){
                endMusic.fadeVolume(0.0, 3.0s);
            }
            // GAME CLEAR GAME RESET
            if(gameClearSeq.endingSeqCounter > 30.0){
                map.ResetMap();
                enemies.clear();
                enemySpawnTime = InitialEnemySpawnInterval;
                enemyAccumulatedTime = 0.0;
                hearts.clear();
                boss.Reset();
                playerController.ResetPlayer();
                title.reset();

                gameStart = false;
                firstLevelStart = false;
                levelTitle.level = 0;

                currentScore = 0;

                gameClearSeq.reset();
                gameClear = false;
                endMusic.stop();
            }
        }

        if (!title.gameStarted)
        {
            if(!titleMusic.isPlaying())
                titleMusic.play();

            title.update();
            continue;
        }

        if(titleMusic.isPlaying())
                titleMusic.stop();

        if(!bgMusic.isPlaying() && !gameClearSeq.gameClear && !gameOver.gameOver)
            bgMusic.play();

        const double deltaTime = Scene::DeltaTime();
        
        //if(!gameOver.gameOver)
        enemyAccumulatedTime += deltaTime;

        while (enemySpawnTime <= enemyAccumulatedTime && map.currentLayer < map.layerCount - 1)
        {
            enemyAccumulatedTime -= enemySpawnTime;
            // enemySpawnTime = Max(enemySpawnTime * 0.95, 0.3);
            // enemies << GenerateEnemy();
            enemies << Enemy(RandomUint8() % (map.currentLayer + 1), &playerController);
        }

        if (!gameStart && title.startingSeqCounter >= 2.4)
        {
            gameStart = true;
        }
        if (gameStart && !firstLevelStart)
        {
            levelTitle.NextLevel();
            gameStart = false;
            firstLevelStart = true;
        }

        // debug
        if (KeyE.down())
        {
            // map.GoToNextLayer();
            // shop.ResetShop();
            // shop.ShowShop();

            // map.ResetMap();
            //enemies.clear();
            //map.MapGameClear();

            //title.reset();

            //gameOver.gameOver = true;
        }

        // GAME OVER
        if(playerController.IsPlayerDead() && !gameOver.gameOver){
            gameOver.gameOver = true;
        }

        // handle layer switching and shop
        if (map.layerSwitched)
        {
            enemies.clear();
            // up to final boss
            if (map.currentLayer < map.layerCount && !map.allLayersCleared)
            {
                // wait for player to finish shopping
                if (!shop.shopActive)
                    shop.ShowShop();

                shop.UpdateShop(playerController);

                if (shop.itemBought)
                {
                    map.StartNextLayer();
                    shop.ResetShop();
                    levelTitle.NextLevel();

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
        if (map.layerSwitched || title.startingSeqCounter < 2.35)
        {
            playerController.Update(deltaTime, false);
            
        }
        else
        {
            playerController.Update(deltaTime, true);
        }

        // EnemyLoop
        if(!gameOver.gameOver){
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
                        if (RandomInt32() % 20 < 1)
                            hearts << Hearts(enemy->GetCollider().center, &playerController);

                        enemySound.stop();
                        bullet->OnHit();
                        effect.add<Spark>(enemy->GetCollider().center,enemy->GetEnemyType());
                        enemy = enemies.erase(enemy);
                        enemySound.play();
                        erased = true;
                        currentScore += enemyScore;
                        break;
                    }
                }

                if (!erased)
                    ++enemy;
            }
        }
        

        UTILS::HeartsLoop(&hearts);

        if (map.currentLayer == map.layerCount - 1 && boss.GetStatus() && !map.layerSwitched)
        {

            boss.Update();
            for (const auto &bullet : playerController.GetBullets())
            {
                if (bullet->GetCollider()->intersects(boss.GetCollider()))
                {
                    bullet->OnHit();
                    boss.GetDamage();
                    break;
                }
            }
        }

        if (map.currentLayer == map.layerCount - 1 && !boss.GetStatus() && !gameClear){
            gameClear = true;
            gameClearSeq.gameClear = true;
            playerController.OnGameClear();
            currentScore += bossScore;
            effect.add<Spark>(boss.GetCollider().center,boss.GetCurretType());
            map.EndLayer();
        }

        // Draw the map
        {

            Graphics2D::SetPSTexture(1, stagePaletteTexture);
            const ScopedCustomShader2D shader{paletteSwap};
            Graphics2D::SetPSConstantBuffer(1, stagePalette[map.currentLayer]);

            map.Draw();
        }
        


        if (levelTitle.isDisplaying) {
            levelTitle.levelTitleTimer += deltaTime;
        }
        if (levelTitle.levelTitleTimer >= levelTitle.levelTitleDisplayTime)
        {
            levelTitle.DisableDisplay();
        }
        levelTitle.DrawLevelTitle();
        
        playerController.Draw(deltaTime);

        {

            // Draw the enemies
            Graphics2D::SetPSTexture(1, enemyPaletteTexture);
            const ScopedCustomShader2D shader{paletteSwap}; // enemy shader palette

            for (auto &enemy : enemies)
            {
                Graphics2D::SetPSConstantBuffer(1, enemyPalette[enemy.GetEnemyType()]);
                enemy.Draw();
            }

            if (map.currentLayer == map.layerCount - 1 && boss.GetStatus())
            {
                Graphics2D::SetPSConstantBuffer(1, enemyPalette[boss.GetCurretType()]);
                boss.Draw();
            }
        }

        for (auto &heart : hearts)
        {
            heart.Draw();
        }

        effect.update();

        shop.DrawShop();

        playerUI.DrawUI(currentScore, playerController.MaxLife(), playerController.Life());



        if (title.gameStarted && title.startingSeqCounter > 0 && title.startingSeqCounter < 3)
        {
            title.update();
        }

        gameOver.update();
        gameClearSeq.update();
    }
}