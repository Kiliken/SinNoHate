# pragma once

# include <Siv3D.hpp>
# include "Button.h"

class Title
{
public:
	
	// Constructor (must be implemented)
	Title();
	~Title();

	// Update function
	void update();

	// Draw function
	void draw();

    void reset();

	bool gameStarted = false;
	bool startingSequence = false;
	float startingSeqCounter = 0;

private:
	Button* playButton;
	const s3d::Texture bg1{Resource(U"Assets/TitlescreenAssets/background1.png")};
	const s3d::Texture bg2{Resource(U"Assets/TitlescreenAssets/background2.png")};
	const s3d::Texture start1{Resource(U"Assets/TitlescreenAssets/start1.png")};
	const s3d::Texture start2{Resource(U"Assets/TitlescreenAssets/start2.png")};
	const s3d::Texture p1{Resource(U"Assets/TitlescreenAssets/player1.png")};
	const s3d::Texture p2{Resource(U"Assets/TitlescreenAssets/player2.png")};
	const s3d::Texture title1{Resource(U"Assets/TitlescreenAssets/title1.png")};
	const s3d::Texture title2{Resource(U"Assets/TitlescreenAssets/title2.png")};
	const s3d::Texture cloudr1{Resource(U"Assets/TitlescreenAssets/cloudright1.png")};
	const s3d::Texture cloudr2{Resource(U"Assets/TitlescreenAssets/cloudright2.png")};
	const s3d::Texture cloudl1{Resource(U"Assets/TitlescreenAssets/cloudleft1.png")};
	const s3d::Texture cloudl2{Resource(U"Assets/TitlescreenAssets/cloudleft2.png")};
	const s3d::Texture inferno{Resource(U"Assets/TitlescreenAssets/inferno.png")};
	const s3d::Texture entry{Resource(U"Assets/TitlescreenAssets/entrys.png")};
	const s3d::Texture finalGlow{Resource(U"Assets/TitlescreenAssets/FinalGlow.png")};
	const s3d::Texture finalFloor{Resource(U"Assets/TitlescreenAssets/FinalFloor.png")};


	Vec2 basePos = Vec2(Scene::Width()/2, Scene::Height()/2);
	Vec2 skyPos = Vec2(Scene::Width()/2, Scene::Height()/2);
	Vec2 cloudRPos = Vec2(Scene::Width()/2, Scene::Height()/2);
	Vec2 cloudLPos = Vec2(Scene::Width()/2, Scene::Height()/2);
	Vec2 fallingPos = Vec2(Scene::Width()/2, Scene::Height()/2);
	Vec2 entryPos = Vec2(Scene::Width()/2, Scene::Height()/2 + 600);
	Vec2 playerSpriteCallibration = Vec2(1,9);


};