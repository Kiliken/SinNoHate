#include "MapManager.h"

Map::Map()
{
    GenerateMap();
}


void Map::GenerateMap()
{
    map.resize(layerCount);
    for (auto& layer : map)
    {
        layer.resize(layerWidth, layerHeight);

        for (int y = 0; y < layerHeight; ++y)
        {
            for (int x = 0; x < layerWidth; ++x)
            {
                int32 tileValue = 0;

                // Simple procedural generation logic
                if (x == 0 || x == layerWidth - 1)  // walls on the sides
                {
                    SetType(tileValue, TileType::wall);
                    SetSprite(tileValue, 1); // wall sprite index
                }
                else if (RandomBool(0.05))
                {
                    SetType(tileValue, TileType::trap);
                    SetSprite(tileValue, 10); // trap sprite index
                }
                else
                {
                    SetType(tileValue, TileType::normal);
                    SetSprite(tileValue, 0); // normal sprite index
                }

                layer[y][x] = tileValue;
            }
        }
    }
}


// draw the map on the screen
void Map::Draw(Texture& mapTex) {
    for (int y = 0; y < layerHeight; y++) {
        for (int x = 0; x < layerWidth; x++) {
            const int32 tile = map[currentLayer][y][x];
            int sprite = GetSprite(tile);
            Vec2 pos(x * tileSize, y * tileSize);
            mapTex(sprite * tileSize, 0, tileSize, tileSize).draw(pos);
        }
    }
}