# include <Siv3D.hpp> // Siv3D v0.6.16
#include "MapManager.h"
#include "PlayerP.h" // placeholder player class
#include "Shop.h"


void Main()
{
    // Create a window
    Window::Resize(512, 480);

    // Load map texture
    Texture mapTexture(U"map.png");

    
    Map map;    // Create map instance
    Shop shop;  // Create shop instance
    Player player;  // placeholder player instance

    while (System::Update())
    {
        if(KeyE.down()) {
            map.GoToNextLayer();
            shop.ResetShop();
            shop.ShowShop();
        }

        map.UpdateTraps(player); // update traps
        shop.UpdateShop(player); // update shop
        // Draw the map
        map.Draw(mapTexture);
        shop.DrawShop();

    }
	
}
