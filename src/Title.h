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

	bool gameStarted = false;

private:
	Button* playButton;
	const s3d::Texture bg1{U"Assets/TitlescreenAssets/background1.png"};
	const s3d::Texture bg2{U"Assets/TitlescreenAssets/background2.png"};
	const s3d::Texture start1{U"Assets/TitlescreenAssets/start1.png"};
	const s3d::Texture start2{U"Assets/TitlescreenAssets/start2.png"};
	const s3d::Texture p1{U"Assets/TitlescreenAssets/player1.png"};
	const s3d::Texture p2{U"Assets/TitlescreenAssets/player2.png"};
	const s3d::Texture title1{U"Assets/TitlescreenAssets/title1.png"};
	const s3d::Texture title2{U"Assets/TitlescreenAssets/title2.png"};
	const s3d::Texture cloudr1{U"Assets/TitlescreenAssets/cloudright1.png"};
	const s3d::Texture cloudr2{U"Assets/TitlescreenAssets/cloudright2.png"};
	const s3d::Texture cloudl1{U"Assets/TitlescreenAssets/cloudleft1.png"};
	const s3d::Texture cloudl2{U"Assets/TitlescreenAssets/cloudleft2.png"};
	const s3d::Texture inferno{U"Assets/TitlescreenAssets/inferno.png"};

};