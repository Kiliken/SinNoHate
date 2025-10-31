#include "InGameUI.h"

UI::UI()
{
    heartTex = TextureAsset(U"HeartTexture");
}

void UI::DrawUI(int score, int maxHP, int currentHP){
    // draw hearts
    int hp = currentHP;
    for (int i = 0; i < maxHP; i++){
        Vec2 pos;
        if(i < 5){
            pos = heartStartPos + Vec2(heartSize * i, 0);
        }
        else{
            pos = heartStartPos + Vec2(heartSize * (i - 5), heartSize);
        }

        if(hp > 0){
            heartTex(fullIndex * heartSize, 0, heartSize, heartSize).draw(pos);
            hp--;
        }
        else{
            heartTex(emptyIndex * heartSize, 0, heartSize, heartSize).draw(pos);
        }
    }

    // draw score
    FontAsset(U"Text")(U"Score: {}"_fmt(score)).draw(16, Arg::topRight = scorePos, Palette::White);
}