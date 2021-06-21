#include "Game/AI/Action/actionCurseRRematchCount.h"
#include "Game/DLC/aocChampionBalladManager.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

CurseRRematchCount::CurseRRematchCount(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CurseRRematchCount::~CurseRRematchCount() = default;

bool CurseRRematchCount::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CurseRRematchCount::loadParams_() {
    getDynamicParam(&mRematchCount_d, "RematchCount");
    getDynamicParam(&mCurseRType_d, "CurseRType");
    getDynamicParam(&mGameDataStringCounterName_d, "GameDataStringCounterName");
}

bool CurseRRematchCount::oneShot_() {
    auto* manager = ChampionBalladManager::instance();
    if (!manager)
        return false;

    auto blight = BlightType(*mCurseRType_d);
    if (blight > BlightType::Water)
        return false;

    if (*mRematchCount_d == 0)
        manager->incrementBlightRematchCount(blight);
    else if (*mRematchCount_d == 1)
        manager->setBlightRematchCount(0, blight);
    else
        return false;

    if (mGameDataStringCounterName_d.isEmpty())
        return true;

    auto* game_data_manager = ksys::gdt::Manager::instance();
    if (game_data_manager) {
        s8 rematchCount = manager->getBlightRematchCount(blight);
        game_data_manager->setS32(rematchCount, mGameDataStringCounterName_d);
        return true;
    }
    return false;
}

}  // namespace uking::action
