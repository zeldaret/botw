#include "Game/AI/Action/actionLevelFlyRiseLookingTarget.h"

namespace uking::action {

LevelFlyRiseLookingTarget::LevelFlyRiseLookingTarget(const InitArg& arg) : LevelFlyLook(arg) {}

LevelFlyRiseLookingTarget::~LevelFlyRiseLookingTarget() = default;

bool LevelFlyRiseLookingTarget::init_(sead::Heap* heap) {
    return LevelFlyLook::init_(heap);
}

void LevelFlyRiseLookingTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    LevelFlyLook::enter_(params);
}

void LevelFlyRiseLookingTarget::leave_() {
    LevelFlyLook::leave_();
}

void LevelFlyRiseLookingTarget::loadParams_() {
    LevelFlyLook::loadParams_();
}

void LevelFlyRiseLookingTarget::calc_() {
    LevelFlyLook::calc_();
}

}  // namespace uking::action
