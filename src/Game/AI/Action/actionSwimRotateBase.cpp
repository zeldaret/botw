#include "Game/AI/Action/actionSwimRotateBase.h"

namespace uking::action {

SwimRotateBase::SwimRotateBase(const InitArg& arg) : WaterFloatBase(arg) {}

SwimRotateBase::~SwimRotateBase() = default;

bool SwimRotateBase::init_(sead::Heap* heap) {
    return WaterFloatBase::init_(heap);
}

void SwimRotateBase::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterFloatBase::enter_(params);
}

void SwimRotateBase::leave_() {
    WaterFloatBase::leave_();
}

void SwimRotateBase::loadParams_() {
    WaterFloatBase::loadParams_();
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getStaticParam(&mRotRatio_s, "RotRatio");
}

void SwimRotateBase::calc_() {
    WaterFloatBase::calc_();
}

}  // namespace uking::action
