# include "GameClear.h"


GameClear::GameClear()
{
	
}


GameClear::~GameClear()
{

}


// Update function
void GameClear::update()
{
	const double deltaTime = Scene::DeltaTime();

	if (gameClear) {
		endingSeqCounter += deltaTime;
		if (endingSeqCounter <= 6)  {
            bottomPos += deltaTime * Vec2(0, -82);
            playerEndPos += deltaTime * Vec2(0, 72.5);
        } else if (endingSeqCounter >= 20.0 && endingSeqCounter <= 23.0) {
            bottomPos += deltaTime * Vec2(0, 100);
            playerEndPos += deltaTime * Vec2(0, -90);
        } else if (endingSeqCounter >= 23.0 && endingSeqCounter <= 25.0) {
            bottomPos += deltaTime * Vec2(0, 100);
        } else if (endingSeqCounter >= 25.0 && endingSeqCounter <= 30.0) {
            bgColor = Math::Min(bgColor + 0.2f * static_cast<float>(deltaTime), 1.0f);
            alpha = Math::Max(alpha - 0.33f * static_cast<float>(deltaTime), 0.0f);
        }
	}



	draw();
}


void GameClear::reset()
{
    gameClear = false;
    // Animation control flags
    endingSeqCounter = 0.0;



    // Reset all positions
    bottomPos = Vec2(Scene::Width()/2, Scene::Height()/2 + 500);
	playerEndPos = Vec2(Scene::Width()/2, Scene::Height()/2 - 300);
    bgColor = 0.01f;
    alpha = 1.0f;

}



// Draw function
void GameClear::draw()
{
	Scene::SetBackground(ColorF{ 0.3, 0.3, 0.3 });
	if (gameClear){
        Scene::Rect().draw(ColorF(bgColor, bgColor, bgColor));

        if (endingSeqCounter <= 17.99) {
            finalGlow.drawAt(bottomPos);
        } else if (endingSeqCounter <= 25.0) {
            finalFloor.drawAt(bottomPos);
        }
		
        if (endingSeqCounter <= 7.0) {
            p8.drawAt(playerEndPos);
        } else if (endingSeqCounter <= 9.0) {
            p7.drawAt(playerEndPos);
        } else if (endingSeqCounter <= 11.0) {
            p6.drawAt(playerEndPos);
        } else if (endingSeqCounter <= 13.0) {
            p5.drawAt(playerEndPos);
        } else if (endingSeqCounter <= 15.0) {
            p4.drawAt(playerEndPos);
        } else if (endingSeqCounter <= 17.0) {
            p3.drawAt(playerEndPos);
        } else if (endingSeqCounter <= 18.0) {
            p2.drawAt(playerEndPos);
        } else if (endingSeqCounter <= 20.0) {
            p1.drawAt(playerEndPos);
        } else if (endingSeqCounter <= 30.0) {
            p1.flipped().drawAt(playerEndPos.x, playerEndPos.y, ColorF(1.0, 1.0, 1.0, alpha));
        }
	} 

	

}

