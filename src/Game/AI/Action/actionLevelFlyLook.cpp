#include "Game/AI/Action/actionLevelFlyLook.h"

namespace uking::action {

LevelFlyLook::LevelFlyLook(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LevelFlyLook::~LevelFlyLook() = default;

bool LevelFlyLook::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LevelFlyLook::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void LevelFlyLook::leave_() {
    ksys::act::ai::Action::leave_();
}

void LevelFlyLook::loadParams_() {
    getStaticParam(&mHeight_s, "Height");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void LevelFlyLook::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
