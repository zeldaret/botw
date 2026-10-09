#include "Game/Actor/Action/actionMove2HomePos.h"

namespace uking::action {

Move2HomePos::Move2HomePos(const InitArg& arg) : MoveHomePosBase(arg) {}

Move2HomePos::~Move2HomePos() = default;

bool Move2HomePos::init_(sead::Heap* heap) {
    return MoveHomePosBase::init_(heap);
}

void Move2HomePos::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveHomePosBase::enter_(params);
}

void Move2HomePos::leave_() {
    MoveHomePosBase::leave_();
}

void Move2HomePos::loadParams_() {
    MoveHomePosBase::loadParams_();
    getStaticParam(&mVibDirection_s, "VibDirection");
    getStaticParam(&mVibPattern_s, "VibPattern");
    getStaticParam(&mVibPower_s, "VibPower");
    getStaticParam(&mVibRange_s, "VibRange");
    getStaticParam(&mIsVibration_s, "IsVibration");
}

void Move2HomePos::calc_() {
    MoveHomePosBase::calc_();
}

}  // namespace uking::action
