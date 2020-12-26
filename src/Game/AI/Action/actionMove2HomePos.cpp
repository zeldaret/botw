#include "Game/AI/Action/actionMove2HomePos.h"

namespace uking::action {

Move2HomePos::Move2HomePos(const InitArg& arg) : Move2HomePosBase(arg) {}

Move2HomePos::~Move2HomePos() = default;

bool Move2HomePos::init_(sead::Heap* heap) {
    return Move2HomePosBase::init_(heap);
}

void Move2HomePos::enter_(ksys::act::ai::InlineParamPack* params) {
    Move2HomePosBase::enter_(params);
}

void Move2HomePos::leave_() {
    Move2HomePosBase::leave_();
}

void Move2HomePos::loadParams_() {
    Move2HomePosBase::loadParams_();
    getStaticParam(&mVibDirection_s, "VibDirection");
    getStaticParam(&mVibPattern_s, "VibPattern");
    getStaticParam(&mVibPower_s, "VibPower");
    getStaticParam(&mVibRange_s, "VibRange");
    getStaticParam(&mIsVibration_s, "IsVibration");
}

void Move2HomePos::calc_() {
    Move2HomePosBase::calc_();
}

}  // namespace uking::action
