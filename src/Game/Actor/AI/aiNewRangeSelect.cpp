#include "Game/Actor/AI/aiNewRangeSelect.h"

namespace uking::ai {

NewRangeSelect::NewRangeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NewRangeSelect::~NewRangeSelect() = default;

bool NewRangeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NewRangeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NewRangeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NewRangeSelect::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mIsSelectEveryFrame_s, "IsSelectEveryFrame");
}

}  // namespace uking::ai
