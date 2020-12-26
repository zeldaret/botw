#include "Game/AI/Action/actionGameDataConvertIntToSring.h"

namespace uking::action {

GameDataConvertIntToSring::GameDataConvertIntToSring(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

GameDataConvertIntToSring::~GameDataConvertIntToSring() = default;

bool GameDataConvertIntToSring::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GameDataConvertIntToSring::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GameDataConvertIntToSring::leave_() {
    ksys::act::ai::Action::leave_();
}

void GameDataConvertIntToSring::loadParams_() {
    getDynamicParam(&mGameDataIntInput_d, "GameDataIntInput");
    getDynamicParam(&mGameDataStringOutput_d, "GameDataStringOutput");
}

void GameDataConvertIntToSring::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
