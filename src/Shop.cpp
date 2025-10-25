#include "Shop.h"


Shop::Shop() {
    // Constructor implementation (if needed)
    AddItems();
}


void Shop::AddItems() {
    // get array of all possible items
    Array<ItemType> possibleItems = { heart, bullet, atkSpd };

    // Add 3 items from list
    for (int i = 0; i < 3; ++i) {
        Item newItem;
        newItem.type = possibleItems[i];
        newItem.name = itemNames[possibleItems[i]];
        newItem.rect = Rect(startX + i * (itemW + spacing), y, itemW, itemH); // debug rect positions
        itemsInShop.push_back(newItem);
        Console << U"Added item to shop: " << newItem.name;
    }
}


// placeholder buy item function
void Shop::BuyItem(ItemType item, PlayerController& player) {
    switch (item) {
    case heart:
        player.UpGrade_IncreaseMaxLife(lifeIncrease);
        Console << U"Bought Heart! Max HP: " << player.MaxLife();
        break;
    case bullet:
        // Implement bullet upgrade
        player.UpGrade_ExpansionBullet(bulletExpansion);
        Console << U"Bought Bullet Upgrade!";
        break;
    case atkSpd:
        // Implement attack speed upgrade
        player.UpGrade_DecreaseAttackSpan(attackSpeedDecrease);
        Console << U"Bought Attack Speed Upgrade!";
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
    //AddItems();
}


void Shop::UpdateShop(PlayerController& player) {
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
    Rect(bgPos.x, bgPos.y, bgSize.x, bgSize.y).draw(ColorF(0.0, 0.0, 0.0, 0.7));

    font(U"Select Upgrade").drawAt(24, center - Vec2(0, 90), Palette::White);

    // Draw items DEBUG
    for (const auto& item : itemsInShop) {
        const ColorF col = itemBought ? ColorF(0.5, 0.5, 0.5) : ColorF(1.0, 1.0, 1.0);
        item.rect.drawFrame(2, 0, col);
        font(item.name).drawAt(12, item.rect.center() + Vec2(0, 70), col);
    }
}