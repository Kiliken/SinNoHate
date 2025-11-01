#include "LevelTitle.h"

LevelTitle::LevelTitle()
{
    levelCardSFX = AudioAsset(U"LevelCardSFX");
}

void LevelTitle::NextLevel(){
    level++;
    isDisplaying = true;

    levelCardSFX.stop();
    levelCardSFX.play();
}

void LevelTitle::DisableDisplay(){
    isDisplaying = false;
    levelTitleTimer = 0.0f;
}


void LevelTitle::DrawLevelTitle(){
    Vec2 pos = basePos + Vec2(0, 100);

    if (!isDisplaying) return;
    switch(level){
        case 1:
            SlothText.drawAt(pos);
            break;
        case 2:
            GluttonyText.drawAt(pos);
            break;
        case 3:
            SorrowText.drawAt(pos);
            break;
        case 4:
            PrideText.drawAt(pos);
            break;
        case 5:
            LustText.drawAt(pos);
            break;
        case 6:
            EnvyText.drawAt(pos);
            break;
        case 7:
            WrathText.drawAt(pos);
            break;
        default:
            break;
    }
}