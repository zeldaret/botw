#include "Game/AI/AI/aiGameDataFlagSelector.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::ai {

GameDataFlagSelector::GameDataFlagSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GameDataFlagSelector::~GameDataFlagSelector() {
    ;
}

bool GameDataFlagSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GameDataFlagSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    bool value = false;
    if (!mClearFlag_m.isEmpty())
        ksys::gdt::Manager::instance()->getParam().get().getBool(&value, mClearFlag_m);
    if (value)
        changeChild("True");
    else
        changeChild("False");
}

void GameDataFlagSelector::calc_() {}

void GameDataFlagSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GameDataFlagSelector::loadParams_() {
    getStaticParam(&mCheckOnEnterOnly_s, "CheckOnEnterOnly");
    getMapUnitParam(&mClearFlag_m, "ClearFlag");
}

}  // namespace uking::ai
