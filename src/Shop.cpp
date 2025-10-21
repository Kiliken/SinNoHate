#include "Shop.h"

Shop::Shop() {
    // Constructor implementation (if needed)
    AddItems();
}


void Shop::AddItems() {
    // get array of all possible items
    Array<ItemType> possibleItems;
    for (int i = 0; i < itemNames.size(); ++i) {
        possibleItems.push_back(static_cast<ItemType>(i));
    }

    // Shuffle the possible items
    possibleItems.shuffle();

    // Clear current items in shop
    itemsInShop.clear();

    // Add first 3 items from shuffled list
    for (int i = 0; i < 3; ++i) {
        Item newItem;
        newItem.type = possibleItems[i];
        newItem.name = itemNames[possibleItems[i]];
        newItem.rect = Rect(100 + i * 150, 200, 100, 100); // debug rect positions
        itemsInShop.push_back(newItem);
        Console << U"Added item to shop: " << newItem.name;
    }
}


// placeholder buy item function
void Shop::BuyItem(ItemType item, Player& player) {
    switch (item) {
    case heart:
        player.maxHP += 1;
        player.currentHP += 1;
        Console << U"Bought Heart! Max HP: " << player.maxHP;
        break;
    case bullet:
        // Implement bullet upgrade
        Console << U"Bought Bullet Upgrade!";
        break;
    case atkDmg:
        // Implement attack damage upgrade
        Console << U"Bought Attack Damage Upgrade!";
        break;
    case atkSpd:
        // Implement attack speed upgrade
        Console << U"Bought Attack Speed Upgrade!";
        break;
    case moveSpd:
        // Implement movement speed upgrade
        Console << U"Bought Movement Speed Upgrade!";
        break;
    default:
        Console << U"Unknown item!";
        break;
    }
    itemBought = true;
}


void Shop::ShowShop() {
    shopActive = true;
}


void Shop::ResetShop() {
    shopActive = false;
    itemBought = false;
    AddItems();
}


void Shop::UpdateShop(Player& player) {
    if (!shopActive) return;

    if (MouseL.down() && !itemBought) {
        const Point mousePos = Cursor::Pos();

        for (const auto& item : itemsInShop) {
            if (item.rect.contains(mousePos)) {
                BuyItem(item.type, player);
                break;
            }
        }
    }
}


void Shop::DrawShop() {
    if (!shopActive) return;

    // Draw shop background DEBUG
    Rect(50, 150, 500, 300).draw(ColorF(0.0, 0.0, 0.0, 0.7));

    // Draw items DEBUG
    for (const auto& item : itemsInShop) {
        item.rect.drawFrame(2, 0, itemBought ? ColorF(0.5, 0.5, 0.5) : ColorF(1.0, 1.0, 1.0));
        FontAsset(U"Default")(item.name).drawAt(item.rect.center(), itemBought ? ColorF(0.5, 0.5, 0.5) : ColorF(1.0, 1.0, 1.0));
    }
}