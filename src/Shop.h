#pragma once
#include <Siv3D.hpp> // Siv3D v0.6.16
#include "Player/PlayerController.h"

class Shop {
public:
    // place holder item types
    enum ItemType
    {
        heart,
        bullet,
        atkDmg,
        atkSpd,
        moveSpd
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
    const Array<String> itemNames = { U"Heart", U"Bullet", U"Attack Damage", U"Attack Speed", U"Movement Speed" };  // placeholder names
    Array<Item> itemsInShop;   // 3 items
};