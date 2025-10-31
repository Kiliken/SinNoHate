#pragma once
#include <Siv3D.hpp> // Siv3D v0.6.16
#include "Player/PlayerController.h"
#include "MapManager.h"

class UI{
    public:
        UI();
        void DrawUI(int score, int maxHP, int currentHP);
        void SetUIActive(bool active);

        
    private:
        Texture heartTex;
        bool isActive = true;
        const int heartSize = 32;
        const int fullIndex = 0;
        const int emptyIndex = 1;
        const Vec2 heartStartPos{32, 32};
        const Vec2 scorePos{Map::screenW - 32, 32};



        //void GenerateHearts();
};