#include "Game/AI/AI/aiRangeSelectAction.h"

namespace uking::ai {

RangeSelectAction::RangeSelectAction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RangeSelectAction::~RangeSelectAction() = default;

bool RangeSelectAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RangeSelectAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RangeSelectAction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RangeSelectAction::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mIsSelectEveryFrame_s, "IsSelectEveryFrame");
    getStaticParam(&mIsRangeXZ_s, "IsRangeXZ");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
