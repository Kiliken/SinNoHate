# pragma once

# include <Siv3D.hpp>
# include "Button.h"
#include "MapManager.h"

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

    void reset();

    void OnMenuBtnPress();

    bool menuBtnPressed = false;
    bool gameOver = false;
	float startingSeqCounter = 0;

private:
	Button* menuButton;
	const s3d::Texture curtainL{Resource(U"Assets/GameOverScreenAssets/CurtainLeft.png")};
	const s3d::Texture curtainR{Resource(U"Assets/GameOverScreenAssets/CurtainRight.png")};
	const s3d::Texture gameOverTexture{Resource(U"Assets/GameOverScreenAssets/GameOver.png")};
	const s3d::Texture menuButtonTexture{Resource(U"Assets/GameOverScreenAssets/MenuButton.png")};


	const Vec2 basePos = Vec2(Scene::Width()/2, Scene::Height()/2);
    const Vec2 gameOverPos = basePos;
    const Vec2 menuBtnPos = basePos;
    const Vec2 curtainLPos = Vec2(0, Scene::Height()/2);
    const Vec2 curtainRPos = Vec2(Scene::Width(), Scene::Height()/2);

    Vec2 curtainLPosC = curtainLPos;
    Vec2 curtainRPosC = curtainRPos;

    bool showText = false;
};