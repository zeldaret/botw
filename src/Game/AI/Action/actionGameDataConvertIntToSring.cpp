#include "Game/AI/Action/actionGameDataConvertIntToSring.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

GameDataConvertIntToSring::GameDataConvertIntToSring(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

GameDataConvertIntToSring::~GameDataConvertIntToSring() = default;

bool GameDataConvertIntToSring::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool GameDataConvertIntToSring::oneShot_() {
    auto* gdm = ksys::gdt::Manager::instance();
    if (!gdm)
        return false;

    int value;
    gdm->getParam().get().getS32(&value, mGameDataIntInput_d);

    sead::FixedSafeString<64> str;
    str.format("%02d", value);
    gdm->setStr(str.cstr(), mGameDataStringOutput_d);

    return true;
}

void GameDataConvertIntToSring::loadParams_() {
    getDynamicParam(&mGameDataIntInput_d, "GameDataIntInput");
    getDynamicParam(&mGameDataStringOutput_d, "GameDataStringOutput");
}

}  // namespace uking::action
