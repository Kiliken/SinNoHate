#include "Shop.h"


Shop::Shop() {
    itemTexture = TextureAsset(U"ShopTexture");
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
        //Console << U"Added item to shop: " << newItem.name;
    }

    //confirmButton = Rect((Map::screenW - 120) / 2, y + itemH + 80, 120, 40);
}


// placeholder buy item function
void Shop::BuyItem(ItemType item, PlayerController& player) {
    switch (item) {
    case heart:
        player.UpGrade_IncreaseMaxLife(lifeIncrease);
        //Console << U"Bought Heart! Max HP: " << player.MaxLife();
        break;
    case bullet:
        // Implement bullet upgrade
        player.UpGrade_ExpansionBullet(bulletExpansion);
        //Console << U"Bought Bullet Upgrade!";
        break;
    case atkSpd:
        // Implement attack speed upgrade
        player.UpGrade_DecreaseAttackSpan(attackSpeedDecrease);
        //Console << U"Bought Attack Speed Upgrade!";
        break;
    default:
        //Console << U"Unknown item!";
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
    selectedItem.reset();
    //AddItems();
}


void Shop::UpdateShop(PlayerController& player) {
    if (!shopActive || itemBought) return;

    // buy if confirm button is visible and clicked
    if (selectedItem && confirmButton.leftClicked()) {
        BuyItem(*selectedItem, player);
        return;
    }

    if (MouseL.down() && !itemBought) {
        const Point mousePos = Cursor::Pos();

        // select item
        for (const auto& item : itemsInShop) {
            if (item.rect.contains(mousePos)) {
                selectedItem = item.type;
                break;
            }
        }
    }
}


void Shop::DrawShop() {
    if (!shopActive) return;

    // Draw shop background DEBUG
    Rect(bgPos.x, bgPos.y, bgSize.x, bgSize.y).draw(ColorF(0.0, 0.0, 0.0, 0.7));

    FontAsset(U"Text")(U"Select Upgrade").drawAt(18, center - Vec2(0, 100), Palette::White);

    // Draw items
    for (const auto& item : itemsInShop) {
        ColorF col = ColorF(1.0);
        if (itemBought) col = ColorF(0.5);
        else if (selectedItem && item.type == *selectedItem) col = ColorF(1.0, 0.8, 0.2); // highlight selected

        item.rect.drawFrame(3, 0, col);
        itemTexture(item.type * Map::tileSize * 2, 0, Map::tileSize * 2, Map::tileSize * 2).drawAt(item.rect.center());
        FontAsset(U"Text")(item.name).drawAt(12, item.rect.center() + Vec2(0, 70), col);
    }

    // Draw confirm button only if an item is selected and not bought yet
    if (selectedItem && !itemBought) {
        const bool hovered = confirmButton.mouseOver();
        const ColorF btnColor = hovered ? ColorF(1) : ColorF(0.5);
        confirmButton.drawFrame(3, 0, btnColor);
        FontAsset(U"Text")(U"Confirm").drawAt(12, confirmButton.center(), Palette::White);
    }
}