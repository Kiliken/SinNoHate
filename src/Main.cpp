# include <Siv3D.hpp>
# include "Title.h"
# include "Game.h"
# include "Enemy.h"


#if true

// Function to create random enemy position
Vec2 GenerateEnemy()
{
	return RandomVec2({ 20, Scene::Width() - 20 }, Scene::Height() + 20);
}

void Main()
{

	Window::Resize(512, 480);

	Scene::SetBackground(ColorF{ 0.1, 0.2, 0.7 });

	const Font font{ FontMethod::MSDF, 48 };

	// Player texture
	const Texture playerTexture{ U"🤖"_emoji };
	// Enemy texture
	const Texture enemyTexture{ U"👾"_emoji };

	TextureAsset::Register(U"EnemyTexture", U"👾"_emoji);

	// Player
	Vec2 playerPos{ 400, 500 };
	// Enemy
	
	//Array<Vec2> enemies = { GenerateEnemy() };
	Array<Enemy> newEnemies = { Enemy(GenerateEnemy(), 1, 1) };
	// Player shots
	Array<Vec2> playerBullets;
	// Enemy shots
	Array<Vec2> enemyBullets;

	// Player speed
	constexpr double PlayerSpeed = 550.0;
	// Player shot speed
	constexpr double PlayerBulletSpeed = 500.0;
	// Enemy speed
	constexpr double EnemySpeed = 100.0;
	// Enemy shot speed
	constexpr double EnemyBulletSpeed = 300.0;

	// Initial enemy spawn interval (seconds)
	constexpr double InitialEnemySpawnInterval = 2.0;
	// Enemy spawn interval (seconds)
	double enemySpawnTime = InitialEnemySpawnInterval;
	// Enemy spawn accumulated time (seconds)
	double enemyAccumulatedTime = 0.0;

	// Player shot cooltime (seconds)
	constexpr double PlayerShotCoolTime = 0.1;
	// Player shot cooltime timer (seconds)
	double playerShotTimer = 0.0;

	// Enemy shot cooltime (seconds)
	constexpr double EnemyShotCoolTime = 0.9;
	// Enemy shot cooltime timer (seconds)
	double enemyShotTimer = 0.0;

	Effect effect;

	// High score
	int32 highScore = 0;
	// Current score
	int32 score = 0;

    int i = 0;

	while (System::Update())
	{
		// Game over check
		bool gameover = false;
        //const uint8_t randCicle = RandomUint8();
		const double deltaTime = Scene::DeltaTime();
		enemyAccumulatedTime += deltaTime;
		playerShotTimer = Min((playerShotTimer + deltaTime), PlayerShotCoolTime);
		enemyShotTimer += deltaTime;

		// Generate enemies
		while (enemySpawnTime <= enemyAccumulatedTime)
		{
			enemyAccumulatedTime -= enemySpawnTime;
			enemySpawnTime = Max(enemySpawnTime * 0.95, 0.3);
			//enemies << GenerateEnemy();
			newEnemies << Enemy(GenerateEnemy(), RandomUint8() % 4, RandomUint8() % 4);
		}

		// Player movement
		const Vec2 move = Vec2{ (KeyRight.pressed() - KeyLeft.pressed()), (KeyDown.pressed() - KeyUp.pressed()) }
			.setLength(deltaTime * PlayerSpeed * (KeyShift.pressed() ? 0.5 : 1.0));
		playerPos.moveBy(move).clamp(Scene::Rect());

		// Player shot firing
		if (PlayerShotCoolTime <= playerShotTimer)
		{
			playerShotTimer -= PlayerShotCoolTime;
			playerBullets << playerPos.movedBy(0, -50);
		}

		// Move player shots
		for (auto& playerBullet : playerBullets)
		{
			playerBullet.y += (deltaTime * -PlayerBulletSpeed);
		}
		// Remove player shots that went off screen
		playerBullets.remove_if([](const Vec2& b) { return (b.y < -40); });

        
		for (auto& enemy : newEnemies)
		{
            
			if(enemy.Update()){
                newEnemies.remove_at(i);
            }
            ++i;
		}
        i = 0;
		/*
		// Move enemies
		for (auto& enemy : enemies)
		{
			enemy.y -= (deltaTime * EnemySpeed);
		}
		// Remove enemies that went off screen
		enemies.remove_if([&](const Vec2& e)
		{
			if (-20 > e.y)
			{
				// Game over if enemy goes off screen
				gameover = true;
				return true;
			}
			else
			{
				return false;
			}
		});
		

		// Fire enemy shots
		if (EnemyShotCoolTime <= enemyShotTimer)
		{
			enemyShotTimer -= EnemyShotCoolTime;

			for (const auto& enemy : enemies)
			{
				enemyBullets << enemy;
			}
		}

		// Move enemy shots
		for (auto& enemyBullet : enemyBullets)
		{
			enemyBullet.y -= (deltaTime * EnemyBulletSpeed);
		}
		// Remove player shots that went off screen
		enemyBullets.remove_if([](const Vec2& b) {return (-20 > b.y); });

		////////////////////////////////
		//
		//	Hit detection
		//
		////////////////////////////////

		// Enemy vs player shot
		for (auto itEnemy = enemies.begin(); itEnemy != enemies.end();)
		{
			const Circle enemyCircle{ *itEnemy, 40 };
			bool skip = false;

			for (auto itBullet = playerBullets.begin(); itBullet != playerBullets.end();)
			{
				if (enemyCircle.intersects(*itBullet))
				{
					// Add explosion effect
					effect.add([pos = *itEnemy](double t)
					{
						const double t2 = ((0.5 - t) * 2.0);
						Circle{ pos, (10 + t * 280) }.drawFrame((20 * t2), ColorF{ 1.0, (t2 * 0.5) });
						return (t < 0.5);
					});

					itEnemy = enemies.erase(itEnemy);
					playerBullets.erase(itBullet);
					++score;
					skip = true;
					break;
				}

				++itBullet;
			}

			if (skip)
			{
				continue;
			}

			++itEnemy;
		}

		// Enemy shot vs player
		for (const auto& enemyBullet : enemyBullets)
		{
			// If enemy shot approaches within 20 pixels of playerPos
			if (enemyBullet.distanceFrom(playerPos) <= 20)
			{
				// Game over
				gameover = true;
				break;
			}
		}
		*/

		// Reset if game over
		if (gameover)
		{
			playerPos = Vec2{ 400, 500 };
			newEnemies.clear();
			playerBullets.clear();
			enemyBullets.clear();
			enemySpawnTime = InitialEnemySpawnInterval;
			highScore = Max(highScore, score);
			score = 0;
		}

		////////////////////////////////
		//
		//	Drawing
		//
		////////////////////////////////

		// Draw background animation
		for (int32 i = 0; i < 12; ++i)
		{
			const double a = Periodic::Sine0_1(2s, Scene::Time() - (2.0 / 12 * i));
			Rect{ 0, (i * 50), 800, 50 }.draw(ColorF(1.0, a * 0.2));
		}

		// Draw player
		playerTexture.resized(80).drawAt(playerPos);

		// Draw player shots
		for (const auto& playerBullet : playerBullets)
		{
			Circle{ playerBullet, 8 }.draw(Palette::Orange);
		}

		/*
		// Draw enemies
		for (const auto& enemy : enemies)
		{
			enemyTexture.resized(60).drawAt(enemy);
		}
		*/
		for (auto& enemy : newEnemies)
		{
			enemy.Draw();
		}

		// Draw enemy shots
		for (const auto& enemyBullet : enemyBullets)
		{
			Circle{ enemyBullet, 4 }.draw(Palette::White);
		}

		// Draw explosion effects
		effect.update();

		// Draw score
		font(U"{} [{}]"_fmt(score, highScore)).draw(30, Arg::bottomRight(780, 580));
	}
}





#else





using App = SceneManager<String>;
 

void Main()
{
	Window::SetTitle(U"TestApp");
	Window::Resize(1280, 720);

	FontAsset::Register(U"TitleFont", FontMethod::MSDF, 48, Typeface::Bold);

	// Create scene manager
	App manager;

	manager.add<Title>(U"Title");
	manager.add<Game>(U"Game");

	manager.setFadeColor(ColorF{ 0.8, 0.9, 1.0 });

	manager.init(U"Title", 0.75s);

	while (System::Update())
	{
		if (not manager.update())
		{
			break;
		}
	}
}

#endif