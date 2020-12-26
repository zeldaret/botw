#include "Game/AI/Action/actionLevelFlyLookDownToTgtHeight.h"

namespace uking::action {

LevelFlyLookDownToTgtHeight::LevelFlyLookDownToTgtHeight(const InitArg& arg) : LevelFlyLook(arg) {}

LevelFlyLookDownToTgtHeight::~LevelFlyLookDownToTgtHeight() = default;

bool LevelFlyLookDownToTgtHeight::init_(sead::Heap* heap) {
    return LevelFlyLook::init_(heap);
}

void LevelFlyLookDownToTgtHeight::enter_(ksys::act::ai::InlineParamPack* params) {
    LevelFlyLook::enter_(params);
}

void LevelFlyLookDownToTgtHeight::leave_() {
    LevelFlyLook::leave_();
}

void LevelFlyLookDownToTgtHeight::loadParams_() {
    LevelFlyLook::loadParams_();
}

void LevelFlyLookDownToTgtHeight::calc_() {
    LevelFlyLook::calc_();
}

}  // namespace uking::action
