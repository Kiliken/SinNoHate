#pragma once
#include <Siv3D.hpp> // Siv3D v0.6.16
#include "Player/PlayerController.h"
#include "MapManager.h"

class Shop {
public:
    // place holder item types
    enum ItemType
    {
        heart,
        bullet,
        atkSpd
    };

    // place holder item struct
    struct Item {
        ItemType type;
        String name;
        Rect rect; // for clicking
    };

    bool shopActive = false;
    bool itemBought = false;


    Shop();
    void AddItems();    // randomly add 3 unrepetitive items
    void BuyItem(ItemType item, PlayerController& player);
    void ShowShop();
    void DrawShop();
    void ResetShop();
    void UpdateShop(PlayerController& player); // handle input


private:
    Font font{ FontMethod::MSDF, 48 };  // placeholder font
    
    const int itemW = 100;
    const int itemH = 100;
    const int numItems = 3;
    const int spacing = 40; // space between items

    // total width occupied by all items and gaps
    const int totalWidth = numItems * itemW + (numItems - 1) * spacing;
    const int startX = (Map::screenW - totalWidth) / 2; // leftmost item x
    const int y = (Map::screenH - itemH) / 2;           // vertically centered

    // screen center
    const Vec2 center{Map::screenW / 2.0, Map::screenH / 2.0};

    // bg centered around screen center
    const Size bgSize{400, 240};
    const Vec2 bgPos{center.x - bgSize.x / 2, center.y - bgSize.y / 2};



    const Array<String> itemNames = { U"Heart", U"Bullet", U"Attack Speed" };  // placeholder names
    Array<Item> itemsInShop;   // 3 items

    int lifeIncrease = 1;
    int bulletExpansion = 5;
    double attackSpeedDecrease = 0.1;
};