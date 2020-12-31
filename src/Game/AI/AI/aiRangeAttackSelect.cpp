#include "Game/AI/AI/aiRangeAttackSelect.h"

namespace uking::ai {

RangeAttackSelect::RangeAttackSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RangeAttackSelect::~RangeAttackSelect() = default;

void RangeAttackSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RangeAttackSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RangeAttackSelect::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mRangeDist_s, "RangeDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mIsIgnoreSmallHit_s, "IsIgnoreSmallHit");
}

}  // namespace uking::ai
