#include <Siv3D.hpp> // Siv3D v0.6.16
#include "Player/PlayerController.h"
#include "MapManager.h"

class LevelTitle{
    public:
        LevelTitle();
        void NextLevel();
        void DrawLevelTitle();
        void DisableDisplay();
        int level = 0;
        float levelTitleDisplayTime = 2.0f;
        bool isDisplaying = false; 
        float levelTitleTimer = 0.0f;
        
        

    private:
        const s3d::Texture SlothText{U"Assets/LevelTitle/Sloth.png"};
        const s3d::Texture GluttonyText{U"Assets/LevelTitle/Gluttony.png"};
        const s3d::Texture SorrowText{U"Assets/LevelTitle/Sorrow.png"};
        const s3d::Texture PrideText{U"Assets/LevelTitle/Pride.png"};
        const s3d::Texture LustText{U"Assets/LevelTitle/Lust.png"};
        const s3d::Texture EnvyText{U"Assets/LevelTitle/Envy.png"};
        const s3d::Texture WrathText{U"Assets/LevelTitle/Wrath.png"};
        Vec2 basePos = Vec2(Scene::Width()/2, Scene::Height()/2);
        
        



};

