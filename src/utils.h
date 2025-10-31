# pragma once
# include <Siv3D.hpp>
# include "MapManager.h"
# include "Player/PlayerController.h"
# include "Shop.h"
# include "Enemy.h"
# include "Hearts.h"
# include "Title.h"
# include "Boss.h"
# include "InGameUI.h"
# include "LevelTitle.h"

namespace UTILS {
    void HeartsLoop(Array<Hearts>* hearts);
}