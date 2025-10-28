# include "Title.h"



Title::Title()
{
	playButton = new Button(Rect{ Scene::Width()/2 -150, Scene::Height()*3/5, 300, 100 }, FontAsset(U"TitleFont"), U"PLAY");
	//quitButton = new Button(Rect{ Scene::Width()/2 -150, Scene::Height()/2, 300, 100 }, FontAsset(U"TitleFont"), U"QUIT");
}

Title::~Title()
{
	playButton = nullptr;
	//quitButton = nullptr;
}

// Update function
void Title::update()
{
	// On left click
	playButton->update();

	if (playButton->clicked())
	{
		gameStarted = true;
	}

	// if (quitButton->clicked())
	// {
	// 	// Transition to game scene
	// 	System::Exit();
	// }
}

// Draw function
void Title::draw()
{
	Scene::SetBackground(ColorF{ 0.3, 0.3, 0.3 });
	if (gameStarted || playButton->hovered()){
		bg2.draw();
		title2.draw();
		
		cloudl2.draw();
		p2.draw();
		cloudr2.draw();
		start2.draw();
	} else {
		bg1.draw();
		title1.draw();
		
		cloudl1.draw();
		p1.draw();
		cloudr1.draw();
		start1.draw();
		inferno.draw();
	}


	// Add japanese text
	FontAsset(U"TitleFont")(String(U"TEST GAME")).drawAt(60, Vec2{ Scene::Size().x/2, Scene::Size().y/8 }, ColorF{ 1, 0.506, 0.09, 1 });

}

