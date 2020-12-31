#include "Game/AI/AI/aiRangeSelect.h"

namespace uking::ai {

RangeSelect::RangeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RangeSelect::~RangeSelect() = default;

bool RangeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RangeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RangeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RangeSelect::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mIsSelectEveryFrame_s, "IsSelectEveryFrame");
}

}  // namespace uking::ai
