# pragma once

# include <Siv3D.hpp>
# include "Button.h"
#include "MapManager.h"

class GameClear
{
public:
	
	// Constructor (must be implemented)
	GameClear();
	~GameClear();

	// Update function
	void update();

	// Draw function
	void draw();

    void reset();

    bool gameClear = false;
	float endingSeqCounter = 0;

private:

	const s3d::Texture finalGlow{Resource(U"Assets/TitlescreenAssets/FinalGlow.png")};
	const s3d::Texture finalFloor{Resource(U"Assets/TitlescreenAssets/FinalFloor.png")};
    const s3d::Texture p1{Resource(U"Assets/TitlescreenAssets/player1.png")};
	const s3d::Texture p2{Resource(U"Assets/TitlescreenAssets/player2.png")};
	const s3d::Texture p3{Resource(U"Assets/TitlescreenAssets/3.png")};
	const s3d::Texture p4{Resource(U"Assets/TitlescreenAssets/4.png")};
	const s3d::Texture p5{Resource(U"Assets/TitlescreenAssets/5.png")};
	const s3d::Texture p6{Resource(U"Assets/TitlescreenAssets/6.png")};
	const s3d::Texture p7{Resource(U"Assets/TitlescreenAssets/7.png")};
	const s3d::Texture p8{Resource(U"Assets/TitlescreenAssets/8.png")};


	const Vec2 basePos = Vec2(Scene::Width()/2, Scene::Height()/2);


    Vec2 bottomPos = Vec2(Scene::Width()/2, Scene::Height()/2 + 500);
	Vec2 playerEndPos = Vec2(Scene::Width()/2, Scene::Height()/2 - 300);
    float bgColor = 0.01f;
    float alpha = 1.0f;


    
};