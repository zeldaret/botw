#include "Game/AI/Action/actionLevelFlyLookRisingToTgtHeight.h"

namespace uking::action {

LevelFlyLookRisingToTgtHeight::LevelFlyLookRisingToTgtHeight(const InitArg& arg)
    : LevelFlyRiseLookingTarget(arg) {}

LevelFlyLookRisingToTgtHeight::~LevelFlyLookRisingToTgtHeight() = default;

bool LevelFlyLookRisingToTgtHeight::init_(sead::Heap* heap) {
    return LevelFlyRiseLookingTarget::init_(heap);
}

void LevelFlyLookRisingToTgtHeight::enter_(ksys::act::ai::InlineParamPack* params) {
    LevelFlyRiseLookingTarget::enter_(params);
}

void LevelFlyLookRisingToTgtHeight::leave_() {
    LevelFlyRiseLookingTarget::leave_();
}

void LevelFlyLookRisingToTgtHeight::loadParams_() {
    LevelFlyRiseLookingTarget::loadParams_();
}

void LevelFlyLookRisingToTgtHeight::calc_() {
    LevelFlyRiseLookingTarget::calc_();
}

}  // namespace uking::action
