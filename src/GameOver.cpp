# include "GameOver.h"



GameOver::GameOver()
{
	menuButton = new Button(Rect{ Scene::Width()/2 -150, Scene::Height()*3/5, 300, 100 }, FontAsset(U"TitleFont"), U"TITLE");
}

GameOver::~GameOver()
{
	menuButton = nullptr;
}

// Update function
void GameOver::update()
{
	const double deltaTime = Scene::DeltaTime();
	// On left click
	menuButton->update();

	if (menuButton->clicked())
	{
		
	}


	if (startingSequence) {
		startingSeqCounter += deltaTime;
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

// Draw function
void GameOver::draw()
{
	Scene::SetBackground(ColorF{ 0.3, 0.3, 0.3 });
	if (startingSequence || playButton->hovered()){
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


}

