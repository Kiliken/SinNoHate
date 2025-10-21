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
        Point position;
        int damage = 1;
        bool activated = false;
        Rect collider;

        Trap(int t, Point pos, int dmg)
            : type(t), position(pos), damage(dmg), activated(false),
              collider(pos.x * tileSize, pos.y * tileSize, tileSize) {}
    };

    int currentLayer = 0;

    Map();

    // map general
	void Draw(Texture& mapTex);

    // trap management
    Array<Trap> traps;
    void CreateTraps();
    void ClearTraps(); // clear all traps
    void UpdateTraps(Player& player); // update traps
    void DrawTraps(Texture& trapTex); // draw traps
    void DestroyTrap(const Trap& trap); // destroy a trap

    // enemy management
    //void CreateEnemies();

private:
    static constexpr int tileSize = 32; // 16?
    static constexpr int layerWidth = 16;
    static constexpr int layerHeight = 60;
    static constexpr int layerCount = 8;

    Array<Grid<int32>> map; // map with layers

    Array<float> trapSpawnChances = { 0.01f, 0.02f, 0.03f, 0.04f, 0.05f, 0.06f, 0.07f, 0.08f }; // per layer
    constexpr static int trapSpawnHeightThreshold = 15; // only spawn traps after this height

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