#include "Game/AI/Action/actionSwimMoveBase.h"

namespace uking::action {

SwimMoveBase::SwimMoveBase(const InitArg& arg) : WaterFloatBase(arg) {}

SwimMoveBase::~SwimMoveBase() = default;

bool SwimMoveBase::init_(sead::Heap* heap) {
    return WaterFloatBase::init_(heap);
}

void SwimMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterFloatBase::enter_(params);
}

void SwimMoveBase::leave_() {
    WaterFloatBase::leave_();
}

void SwimMoveBase::loadParams_() {
    WaterFloatBase::loadParams_();
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getStaticParam(&mFinRadius_s, "FinRadius");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mBaseRotRatio_s, "BaseRotRatio");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void SwimMoveBase::calc_() {
    WaterFloatBase::calc_();
}

}  // namespace uking::action
