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
        double deltaTime = Scene::DeltaTime();

        // debug
        if(KeyE.down()) {
            //map.GoToNextLayer();
            shop.ResetShop();
            shop.ShowShop();
        }

        // handle layer switching and shop
        if(map.layerSwitched) {
            // wait for player to finish shopping
            if(!shop.shopActive)
                shop.ShowShop();

            shop.UpdateShop(player);

            if(shop.itemBought) {
                map.StartNextLayer();
                shop.ResetShop();
            }
        }

        map.UpdateMap(deltaTime, player);
        //shop.UpdateShop(player); // update shop

        // Draw the map
        map.Draw(mapTexture);
        shop.DrawShop();

    }
	
}
