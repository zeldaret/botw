#include "Game/AI/AI/aiNavViewMove.h"

namespace uking::ai {

NavViewMove::NavViewMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NavViewMove::~NavViewMove() = default;

bool NavViewMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NavViewMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NavViewMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NavViewMove::loadParams_() {
    getStaticParam(&mSubsAngle_s, "SubsAngle");
    getStaticParam(&mCheckOnce_s, "CheckOnce");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
