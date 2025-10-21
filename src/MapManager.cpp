#include "MapManager.h"

Map::Map()
{
    GenerateMap();
}


void Map::GenerateMap()
{
    map.resize(layerCount);
    for(int layerIndex = 0; layerIndex < layerCount; ++layerIndex){
        auto& layer = map[layerIndex];
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
                else if (y > trapSpawnHeightThreshold && RandomBool(trapSpawnChances[layerIndex]))  // random trap placement
                {
                    SetType(tileValue, TileType::trap);
                    //SetSprite(tileValue, 0); // trap sprite index
                }
                else
                {
                    //SetType(tileValue, TileType::normal);
                    //SetSprite(tileValue, 0); // normal sprite index
                }

                layer[y][x] = tileValue;
            }
        }
    }

    CreateTraps(); // Initialize traps after generating the map
}


// create traps based on the map data
void Map::CreateTraps()
{
    ClearTraps(); // Clear existing traps

    const auto& currentMapLayer = map[currentLayer];

    for (int y = 0; y < layerHeight; ++y)
    {
        for (int x = 0; x < layerWidth; ++x)
        {
            int32 tileValue = currentMapLayer[y][x];
            if (GetType(tileValue) == TileType::trap)
            {
                // damage set to 1 for now
                traps.emplace_back(0, Point(x, y), 1); // type 0, position (x,y), damage 1
                Console << U"Trap created at (" << x << U"," << y << U")";
            }
        }
    }
}


// clear all traps
void Map::ClearTraps()
{
    traps.clear();
}


// check for player collision with traps
void Map::UpdateTraps(Player& player)
{
    // DEBUG
    // if(KeySpace.down()){
    //     //ClearTraps(); // clear all traps

    //     // only destroy one trap per key press
    //     //DestroyTrap(traps[0]);

    // }
    for (auto& trap : traps)
    {
        if(player.collider.intersects(trap.collider) && !trap.activated) {
            player.currentHP -= trap.damage;
            trap.activated = true;
            Console << U"Player hit a trap! Current HP: " << player.currentHP;
            DestroyTrap(trap);
        }
    }
}


// for destroying a trap, optionally do something first
void Map::DestroyTrap(const Trap& trap)
{
    // Remove the trap from the array based on its position
    traps.remove_if([&trap](const Trap& t) {
        return t.position == trap.position;
    });
    
    Console << U"Trap at (" << trap.position.x << U"," << trap.position.y << U") destroyed.";
}


void Map::DrawTraps(Texture& trapTex) {
    for (const auto& trap : traps) {
        Vec2 pos(trap.position.x * tileSize, trap.position.y * tileSize);
        trapTex(10 * tileSize, 0, tileSize, tileSize).draw(pos); // assuming trap sprite is at index 10
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
            // if (GetType(tile) == TileType::trap)
            //     mapTex(10 * tileSize, 0, tileSize, tileSize).draw(pos);
        }
    }

    DrawTraps(mapTex); // draw traps on top of the map
}