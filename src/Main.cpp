# include <Siv3D.hpp> // Siv3D v0.6.16
#include "MapManager.h"
#include "PlayerP.h" // placeholder player class

void Main()
{
    // Create a window
    Window::Resize(512, 480);

    // Load map texture
    Texture mapTexture(U"map.png");

    // Create map instance
    Map map;

    Player player;

    while (System::Update())
    {
        map.UpdateTraps(player); // update traps
        // Draw the map
        map.Draw(mapTexture);
    }
	
}
