# include <Siv3D.hpp> // Siv3D v0.6.16
#include "MapManager.h"
#include "Player/PlayerController.h"
#include "Shop.h"


void Main()
{
    // Create a window
    Window::Resize(512, 480);

    // Load map texture
    Texture mapTexture(U"map.png");

    
    Map map;    // Create map instance
    Shop shop;  // Create shop instance
    PlayerController playerController({ 256.0f, 240.0f }); // Create player controller instance

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

            shop.UpdateShop(playerController);

            if(shop.itemBought) {
                map.StartNextLayer();
                shop.ResetShop();
            }
        }

        map.UpdateMap(deltaTime, playerController);
        //shop.UpdateShop(player); // update shop
        playerController.Update(deltaTime);

        // Draw the map
        map.Draw(mapTexture);
        playerController.Draw(deltaTime);
        shop.DrawShop();

    }
	
}
