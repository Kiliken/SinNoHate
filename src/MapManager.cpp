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
                // else if (y > trapSpawnHeightThreshold && RandomBool(trapSpawnChances[layerIndex]))  // random trap placement
                // {
                //     SetType(tileValue, TileType::trap);
                //     //SetSprite(tileValue, 0); // trap sprite index
                // }
                else
                {
                    //SetType(tileValue, TileType::normal);
                    //SetSprite(tileValue, 0); // normal sprite index
                }

                layer[y][x] = tileValue;
            }
            bgTileYPos << y * tileSize; // store background tile y positions
        }
    }

    CreateTraps(); // Initialize traps after generating the map
}


void Map::UpdateMap(double deltaTime, Player& player)
{
    UpdateBackground(deltaTime);
    UpdateTraps(deltaTime, player);

    if(!layerSwitched){
        layerTimer += deltaTime;
        // don't go to next layer if on final layer
        if(layerTimer >= layerTime && currentLayer < layerCount - 1) {
            layerTimer = 0.0f;
            EndLayer();
        }
    }
}


void Map::UpdateBackground(double deltaTime)
{
    // Simple scrolling background logic
    for (auto& yPos : bgTileYPos)
    {
        yPos -= bgScrollSpeed * deltaTime; // scroll speed
        if (yPos < -tileSize)
        {
            yPos += layerHeight * tileSize;
        }
    }
}


// proceed to next layer of the map
void Map::EndLayer()
{
    ClearTraps(); // clear existing traps
    spawningTraps = false; // stop spawning traps for current layer

    if (currentLayer < layerCount - 1)
    {
        currentLayer++;
        Console << U"Layer cleared. Moved to layer " << currentLayer;
    }
    layerSwitched = true;
}


void Map::StartNextLayer()
{
    spawningTraps = true; // resume spawning traps
    layerSwitched = false;
    Console << U"Started layer " << currentLayer;
}


// create traps based on the map data OLD
// void Map::CreateTraps()
// {
//     ClearTraps(); // Clear existing traps

//     const auto& currentMapLayer = map[currentLayer];

//     for (int y = 0; y < layerHeight; ++y)
//     {
//         for (int x = 0; x < layerWidth; ++x)
//         {
//             int32 tileValue = currentMapLayer[y][x];
//             if (GetType(tileValue) == TileType::trap)
//             {
//                 traps.emplace_back(0, Point(x, y), trapDamageValues[currentLayer]);
//                 Console << U"Trap created at (" << x << U"," << y << U")";
//             }
//         }
//     }
// }

// create traps at random times/positions based on spawn chance and max count
void Map::CreateTraps()
{
    // spawn from 0 to max count per layer
    int spawnCount = Random(0, trapSpawnMaxCounts[currentLayer]);

    for(int i = 0; i < spawnCount; ++i) {
        float x = Random(1, layerWidth - 2) * tileSize; // avoid walls
        float y = layerHeight * tileSize;

        // check if position is already occupied by another trap
        bool positionOccupied = false;
        for (const auto& trap : traps) {
            if (trap.position.x == x) {
                positionOccupied = true;
                break;
            }
        }
        if(positionOccupied) continue; // skip this iteration if occupied

        traps.emplace_back(0, Vec2(x, y), trapDamageValues[currentLayer]);
        Console << U"Trap created at (" << x << U"," << y << U")";
    }
}


// clear all traps
void Map::ClearTraps()
{
    traps.clear();
}


// check for player collision with traps
void Map::UpdateTraps(double deltaTime, Player& player)
{
    // DEBUG
    // if(KeySpace.down()){
    //     //ClearTraps(); // clear all traps

    //     // only destroy one trap per key press
    //     //DestroyTrap(traps[0]);

    // }
    for(auto& trap : traps) {
        // move trap downwards
        trap.position.y -= bgScrollSpeed * deltaTime;
        trap.collider.setPos(trap.position.x, trap.position.y);
        trap.explosionCol.setPos(trap.position.x, trap.position.y);
        // remove trap if it goes off screen
        if(trap.position.y < -tileSize) {
            DestroyTrap(trap);
        }
    }

    for (auto& trap : traps)
    {
        // check collision with player and bullets プレイヤーとの当たり判定を確認
        if(CheckTrapCollisions(player) && !trap.activated) {
            trap.activated = true;
            Console << U"Trap at (" << trap.position.x << U"," << trap.position.y << U") activated!";
        }
        else if(trap.activated) {
            // after activation, check explosion collision
            if(player.collider.intersects(trap.explosionCol) && !trap.damagedPlayer) {
                player.currentHP -= trap.damage; // apply damage again
                trap.damagedPlayer = true;
                Console << U"Player hit by trap explosion! Current HP: " << player.currentHP;
            }

            // CHECK ENEMY COLLISION HERE

            // update timer
            trap.timer += deltaTime;
            if(trap.timer >= trap.activeTime) {
                // after active time, destroy the trap
                DestroyTrap(trap);
            }
        }
    }

    // spawn traps over time
    trapSpawnTimer += deltaTime;
    if(trapSpawnTimer >= trapSpawnInterval) {
        trapSpawnTimer = 0.0f;
        if(spawningTraps)
            CreateTraps();
    }
}


// check for collisions between player and its bullets and traps
bool Map::CheckTrapCollisions(Player& player)
{
    for (const auto& trap : traps)
    {
        if (player.collider.intersects(trap.collider))
        {
            return true; // Collision detected
        }
        
        for(const auto& bullet : player.bullets) {
            if(bullet.collider.intersects(trap.collider)) {
                // destroy bullet here later

                return true; // Collision detected
            }
        }

    }
    return false; // No collision
}


// for destroying a trap, optionally do something first
void Map::DestroyTrap(Trap& trap)
{
    // Remove the trap from the array based on its position
    traps.remove_if([&trap](const Trap& t) {
        return t.position == trap.position;
    });
    
    Console << U"Trap at (" << trap.position.x << U"," << trap.position.y << U") destroyed.";
}


// change to actual texture later
void Map::DrawTraps(Texture& trapTex) {
    for (const auto& trap : traps) {
        Vec2 pos(trap.position.x, trap.position.y);
        trapTex(10 * tileSize, 0, tileSize, tileSize).draw(pos); // assuming trap sprite is at index 10
    }
}


// draw the map on the screen
void Map::Draw(Texture& mapTex) {
    for (int y = 0; y < layerHeight; y++) {
        for (int x = 0; x < layerWidth; x++) {
            const int32 tile = map[currentLayer][y][x];
            int sprite = GetSprite(tile);
            Vec2 pos(x * tileSize, Math::Round(bgTileYPos[y]));
            // y will be current layer later
            mapTex(sprite * tileSize, 0, tileSize, tileSize).draw(pos);
            // if (GetType(tile) == TileType::trap)
            //     mapTex(10 * tileSize, 0, tileSize, tileSize).draw(pos);
        }
    }

    DrawTraps(mapTex); // draw traps on top of the map
}