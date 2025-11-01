# pragma once

# include <Siv3D.hpp>
# include "Button.h"
# include "Player/PlayerController.h"

class GameOver
{
public:

	// Constructor (must be implemented)
	GameOver();
	~GameOver();

	// Update function
	void update();

	// Draw function
	void draw();

	bool m_hasGameOver = true;


private:
	Button* menuButton;
	const s3d::Texture curtainL{U"Assets/GameOverScreenAssets/CurtainLeft.png"};
	const s3d::Texture curtainR{U"Assets/GameOverScreenAssets/CurtainRight.png"};
	const s3d::Texture gameOver{U"Assets/GameOverScreenAssets/GameOver.png"};
	const s3d::Texture menuButton{U"Assets/GameOverScreenAssets/MenuButton.png"};


	Vec2 curtainLPos = Vec2(Scene::Width() / 2, Scene::Height() / 2);
	Vec2 curtainRPos = Vec2(Scene::Width() / 2, Scene::Height() / 2);
	Vec2 gameOverPos = Vec2(Scene::Width() / 2, Scene::Height() / 2);
	Vec2 menuButtonPos = Vec2(Scene::Width() / 2, Scene::Height() / 2);


};