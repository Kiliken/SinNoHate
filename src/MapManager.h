#pragma once
#include <Siv3D.hpp> // Siv3D v0.6.16

class Map{
public:
    enum TileType {
        normal,
        wall,
        trap,
    };

    int currentLayer = 0;

    Map();

    // map general
	void Draw(Texture& mapTex);

    // enemy management
    //void CreateEnemies();

private:
    static constexpr int tileSize = 32; // 16?
    static constexpr int layerWidth = 16;
    static constexpr int layerHeight = 60;
    static constexpr int layerCount = 8;

    Array<Grid<int32>> map; // map with layers

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