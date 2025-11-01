# include "GameOver.h"


GameOver::GameOver()
{
	menuButton = new Button(Rect{ Scene::Width()/2 -150, Scene::Height()*3/5, 300, 100 }, FontAsset(U"TitleFont"), U"MENU");
	//quitButton = new Button(Rect{ Scene::Width()/2 -150, Scene::Height()/2, 300, 100 }, FontAsset(U"TitleFont"), U"QUIT");
}


GameOver::~GameOver()
{
	menuButton = nullptr;
	//quitButton = nullptr;
}


// Update function
void GameOver::update()
{
	const double deltaTime = Scene::DeltaTime();

	if (gameOver) {
        if (menuButton->clicked() && !menuBtnPressed)
        {
            // return to menu here
            menuBtnPressed = true;
        }

		startingSeqCounter += deltaTime;
		if (startingSeqCounter <= 0.75)  {
			curtainRPosC += deltaTime * Vec2(-350, 0);
			curtainLPosC += deltaTime * Vec2(350, 0);
		}
		else {
            showText = true;

            // On left click
            menuButton->update();
        }
	}


	draw();
}


void GameOver::reset()
{
    gameOver = false;
    // Animation control flags
    startingSeqCounter = 0.0;
    menuBtnPressed = false;
    showText = false;

    // Reset all positions
    curtainLPosC = curtainLPos;
    curtainRPosC = curtainRPos;

    //Console << U"Game Over screen reset to initial state.";
}

void GameOver::OnMenuBtnPress(){
    reset();
}

// Draw function
void GameOver::draw()
{
	Scene::SetBackground(ColorF{ 0.3, 0.3, 0.3 });
	if (gameOver){
		curtainL.drawAt(curtainLPosC);
        curtainR.drawAt(curtainRPosC);
        if(showText){
            Rect(0, 0, Map::screenW, Map::screenH).draw(ColorF(0.0));
            gameOverTexture.drawAt(gameOverPos);
		    menuButtonTexture.drawAt(menuBtnPos);
        }
	} 

	// Add japanese text
	//FontAsset(U"TitleFont")(String(U"TEST GAME")).drawAt(60, Vec2{ Scene::Size().x/2, Scene::Size().y/8 }, ColorF{ 1, 0.506, 0.09, 1 });

}

