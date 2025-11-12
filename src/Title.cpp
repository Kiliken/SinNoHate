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
	const double deltaTime = Scene::DeltaTime();
	// On left click
    playButton->update();

	if (playButton->clicked())
	{
		startingSequence = true;
		gameStarted = true;

	}



	if (startingSequence) {

		startingSeqCounter += deltaTime;

		const uint64 t = Time::GetMillisec();
        const uint32 x = t / 30 % 2;

        if(x == 1 && n != x && y < 9){
            n = x;
            y++;

        }

        if(x == 0) 
            n = 0;


		
		if (startingSeqCounter <= 1)  {
			cloudLPos += deltaTime * Vec2(-350, 0);
			cloudRPos += deltaTime * Vec2(350, 0);
			
		}
		else if (startingSeqCounter <= 1.65) {
			fallingPos -= deltaTime * Vec2(0, 450);
			entryPos -= deltaTime * Vec2(0,450);
		}
		else if (startingSeqCounter <= 3.5) { 
			fallingPos -= deltaTime * Vec2(0,450);
			skyPos -= deltaTime * Vec2(0, 450);
			entryPos -= deltaTime * Vec2(0,450);
		}
	}


	draw();
}

void Title::reset()
{
    // Animation control flags
    startingSequence = false;
    startingSeqCounter = 0.0;
    gameStarted = false;
	animFin = false;
	y = 0;

	

    // Reset all positions
    basePos = Vec2(Scene::Width() / 2, Scene::Height() / 2);
    skyPos = Vec2(Scene::Width()/2, Scene::Height()/2);
    fallingPos = Vec2(Scene::Width()/2, Scene::Height()/2);;
    entryPos = Vec2(Scene::Width()/2, Scene::Height()/2 + 600);
    cloudLPos = Vec2(Scene::Width()/2, Scene::Height()/2);;
    cloudRPos = Vec2(Scene::Width()/2, Scene::Height()/2);;
    playerSpriteCallibration = Vec2(1,9); 

    //Console << U"Title screen reset to initial state.";
}

// Draw function
void Title::draw()
{
	Scene::SetBackground(ColorF{ 0.3, 0.3, 0.3 });
	if (startingSequence){
		bg2.drawAt(skyPos);
		title2.drawAt(fallingPos);
		cloudl2.drawAt(cloudLPos);
		cloudr2.drawAt(cloudRPos);

		if (!animFin) startAnim((520 * y),0,520,480).drawAt(fallingPos);
		if (y == 8) {
			animFin = true;
		}
		
		
		entry.drawAt(entryPos);
		if (startingSeqCounter < 2.35) {
			p2.drawAt(basePos + playerSpriteCallibration);
		}

	} else if (playButton->hovered()){
		bg2.drawAt(skyPos);
		title2.drawAt(fallingPos);
		cloudl2.drawAt(cloudLPos);
		cloudr2.drawAt(cloudRPos);
		start2.drawAt(fallingPos);

		entry.drawAt(entryPos);
		if (startingSeqCounter < 2.35) {
			p2.drawAt(basePos + playerSpriteCallibration);
		}

	} else {
		bg1.drawAt(basePos);
		title1.drawAt(basePos);
		cloudl1.drawAt(basePos);
		p1.drawAt(basePos + playerSpriteCallibration);
		cloudr1.drawAt(basePos);
		start1.drawAt(basePos);
		inferno.drawAt(basePos);
	}


	// Add japanese text
	FontAsset(U"TitleFont")(String(U"TEST GAME")).drawAt(60, Vec2{ Scene::Size().x/2, Scene::Size().y/8 }, ColorF{ 1, 0.506, 0.09, 1 });

}

