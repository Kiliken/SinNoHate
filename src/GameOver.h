# pragma once

# include <Siv3D.hpp>
# include "Button.h"

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

	bool gameOver = false;
	bool startingSequence = false;
	float startingSeqCounter = 0;

private:
	Button* playButton;
	const s3d::Texture curtainL{Resource(U"Assets/GameOverScreenAssets/CurtainLeft.png")};
	const s3d::Texture curtainR{Resource(U"Assets/GameOverScreenAssets/CurtainRight.png")};
	const s3d::Texture gameOver{Resource(U"Assets/GameOverScreenAssets/GameOver.png")};
	const s3d::Texture menuButton{Resource(U"Assets/GameOverScreenAssets/MenuButton.png")};


	Vec2 basePos = Vec2(Scene::Width()/2, Scene::Height()/2);
	Vec2 skyPos = Vec2(Scene::Width()/2, Scene::Height()/2);
	Vec2 cloudRPos = Vec2(Scene::Width()/2, Scene::Height()/2);
	Vec2 cloudLPos = Vec2(Scene::Width()/2, Scene::Height()/2);
	Vec2 fallingPos = Vec2(Scene::Width()/2, Scene::Height()/2);
	Vec2 entryPos = Vec2(Scene::Width()/2, Scene::Height()/2 + 600);
};