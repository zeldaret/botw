#include "Game/AI/Action/actionGameDataConvertIntToSring.h"

namespace uking::action {

GameDataConvertIntToSring::GameDataConvertIntToSring(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

GameDataConvertIntToSring::~GameDataConvertIntToSring() = default;

bool GameDataConvertIntToSring::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GameDataConvertIntToSring::loadParams_() {
    getDynamicParam(&mGameDataIntInput_d, "GameDataIntInput");
    getDynamicParam(&mGameDataStringOutput_d, "GameDataStringOutput");
}

}  // namespace uking::action
