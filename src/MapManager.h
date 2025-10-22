#pragma once
#include <Siv3D.hpp> // Siv3D v0.6.16
#include "PlayerP.h"    // placeholder player class, change later

class Map{
public:
    enum TileType {
        normal,
        wall,
        trap,
    };

    // trap struct
    struct Trap {
        int type = 0;
        Vec2 position;  // world position
        int damage = 1;
        bool activated = false;
        Rect collider;
        Rect explosionCol;

        Trap(int t, Vec2 pos, int dmg)
            : type(t), position(pos), damage(dmg), activated(false),
              collider(pos.x, pos.y, tileSize), explosionCol(pos.x, pos.y, tileSize * 1.5) {}
    };

    int currentLayer = 0;


    Map();

    // map general
    void UpdateMap(double deltaTime, Player& player);
    void UpdateBackground(double deltaTime);
	void Draw(Texture& mapTex);
    void GoToNextLayer();

    // trap management
    Array<Trap> traps;
    void CreateTraps();
    void ClearTraps(); // clear all traps
    void UpdateTraps(double deltaTime, Player& player); // update traps
    void DrawTraps(Texture& trapTex); // draw traps
    void DestroyTrap(Trap& trap); // destroy a trap

    // enemy management
    //void CreateEnemies();

private:
    static constexpr int tileSize = 32; // 16?
    static constexpr int layerWidth = 16;
    static constexpr int layerHeight = 16;
    static constexpr int layerCount = 8;

    //static constexpr int bgRows = 16; // background tile rows in texture
    Array<float> bgTileYPos; // y positions of background tiles in texture
    float bgScrollSpeed = 60.0f; // background scroll speed

    static constexpr float layerTime = 10.0f; // time per layer in seconds (excluding final layer)
    float layerTimer = 0.0f;

    Array<Grid<int32>> map; // map with layers

    // trap parameters
    //Array<float> trapSpawnChances = { 0.01f, 0.02f, 0.03f, 0.04f, 0.05f, 0.06f, 0.07f, 0.08f }; // per layer
    Array<int> trapSpawnMaxCounts = { 3, 3, 4, 6, 6, 8, 10, 14 }; // per layer
    Array<int> trapDamageValues = { 1, 1, 1, 2, 2, 2, 3, 3 }; // per layer
    //constexpr static int trapSpawnHeightThreshold = 5; // only spawn traps after this height, 15
    float trapSpawnTimer = 0.0f;
    float trapSpawnInterval = 2.0f; // seconds


    void GenerateMap();

    // bit accessors
	// 00 - 07 bits: sprite index on texture
	static int GetSprite(int32 value) { return (value & 0xFF); }
	// 08 - 15 bits: type: 0 - normal, 1 - wall, 2 - trap
	static int GetType(int32 value) { return (value >> 8) & 0xFF; }

    // corresponding setters
	static void SetSprite(int32& value, int idx) { value = (value & ~0xFF) | (idx & 0xFF); }
    static void SetType(int32& value, int idx) { value = (value & ~(0xFF << 8)) | ((idx & 0xFF) << 8); }
};