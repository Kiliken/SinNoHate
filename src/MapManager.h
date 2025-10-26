#pragma once
#include <Siv3D.hpp> // Siv3D v0.6.16
#include "Player/PlayerController.h"
#include "Enemy.h"

class Map{
public:
    enum TileType {
        normal,
        wall,
        trap,
    };

    enum SpriteIndex {
        bg1 = 0,
        bg2 = 1,
        wall1 = 2,
        wall2 = 3,
        trapActive = 4,
    };

    // trap struct
    struct Trap {
        int type = 0;
        Vec2 position;  // world position
        int damage = 1;
        bool activated = false;
        bool damagedPlayer = false;
        float timer = 0.0f;
        float activeTime = 1.0f; // time before explosion
        float explosionSize = tileSize * 1.5f;
        float explosionOffset = tileSize * 0.25f;

        Rect collider;
        Rect explosionCol;
        
        Trap(int t, Vec2 pos, int dmg)
            : type(t), position(pos), damage(dmg), activated(false),
                // set explosion collider 1.5 times bigger than trap collider
              collider(pos.x, pos.y, tileSize), explosionCol(pos.x - explosionOffset, pos.y - explosionOffset, explosionSize){}
    };

    static constexpr int screenW = 512;
    static constexpr int screenH = 480;
    static constexpr int tileSize = 32; // 16?
    static constexpr int layerWidth = 16;
    static constexpr int layerHeight = 16;
    static constexpr int layerCount = 8;
    
    int currentLayer = 0;
    bool layerSwitched = false; // to add delay between layers
    bool reverseScroll = false;


    Map();

    // map general
    void UpdateMap(double deltaTime, PlayerController& player, Array<Enemy>* enemies);
    void UpdateBackground(double deltaTime);
	void Draw();
    void EndLayer();
    void StartNextLayer();

    // trap management
    Array<Trap> traps;
    void CreateTraps();
    void ClearTraps(); // clear all traps
    void UpdateTraps(double deltaTime, PlayerController& player, Array<Enemy>* enemies); // update traps
    void DrawTraps(); // draw traps
    void DestroyTrap(Trap& trap); // destroy a trap

    // enemy management
    //void CreateEnemies();

private:
    Texture mapTexture;

    Array<float> bgTileYPos; // y positions of background tiles in texture
    float bgScrollSpeed = 60.0f; // background scroll speed
    float bgReverseScrollSpeed = -120.0f; // reverse scroll speed
    double scrollOffset = 0.0; // current scroll offset

    static constexpr float layerTime = 10.0f; // time per layer in seconds (excluding final layer)
    float layerTimer = 0.0f;

    Array<Grid<int32>> map; // map with layers

    // trap parameters
    Array<int> trapSpawnMaxCounts = { 3, 3, 4, 6, 6, 8, 10, 14 }; // per layer
    Array<int> trapDamageValues = { 1, 1, 1, 1, 1, 1, 1, 1 }; // per layer
    float trapSpawnTimer = 0.0f;
    float trapSpawnInterval = 2.0f; // seconds
    bool spawningTraps = true;


    void GenerateMap();

    bool CheckTrapCollisions(Trap& trap, PlayerController& player);

    // bit accessors
	// 00 - 07 bits: sprite index on texture
	static int GetSprite(int32 value) { return (value & 0xFF); }
	// 08 - 15 bits: type: 0 - normal, 1 - wall, 2 - trap
	static int GetType(int32 value) { return (value >> 8) & 0xFF; }

    // corresponding setters
	static void SetSprite(int32& value, int idx) { value = (value & ~0xFF) | (idx & 0xFF); }
    static void SetType(int32& value, int idx) { value = (value & ~(0xFF << 8)) | ((idx & 0xFF) << 8); }
};