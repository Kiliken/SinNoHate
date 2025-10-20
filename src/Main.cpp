# include <Siv3D.hpp> // Siv3D v0.6.16
#include "MapManager.h"

void Main()
{
    // Create a window
    Window::Resize(512, 480);

    // Load map texture
    Texture mapTexture(U"map.png");

    // Create map instance
    Map map;

    while (System::Update())
    {
        // Draw the map
        map.Draw(mapTexture);
    }
	
}
