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
        Audio levelCardSFX;
        const s3d::Texture SlothText{Resource(U"Assets/LevelTitle/Sloth.png")};
        const s3d::Texture GluttonyText{Resource(U"Assets/LevelTitle/Gluttony.png")};
        const s3d::Texture SorrowText{Resource(U"Assets/LevelTitle/Sorrow.png")};
        const s3d::Texture PrideText{Resource(U"Assets/LevelTitle/Pride.png")};
        const s3d::Texture LustText{Resource(U"Assets/LevelTitle/Lust.png")};
        const s3d::Texture EnvyText{Resource(U"Assets/LevelTitle/Envy.png")};
        const s3d::Texture WrathText{Resource(U"Assets/LevelTitle/Wrath.png")};
        
        Vec2 basePos = Vec2(Scene::Width()/2, Scene::Height()/2);
        
        



};

