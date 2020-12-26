#include "Game/AI/Action/actionHornUse.h"

namespace uking::action {

HornUse::HornUse(const InitArg& arg) : HornUseBase(arg) {}

HornUse::~HornUse() = default;

bool HornUse::init_(sead::Heap* heap) {
    return HornUseBase::init_(heap);
}

void HornUse::enter_(ksys::act::ai::InlineParamPack* params) {
    HornUseBase::enter_(params);
}

void HornUse::leave_() {
    HornUseBase::leave_();
}

void HornUse::loadParams_() {
    HornUseBase::loadParams_();
    getStaticParam(&mSpreadDist_s, "SpreadDist");
    getStaticParam(&mSpreadTime_s, "SpreadTime");
    getStaticParam(&mTerrorLevel_s, "TerrorLevel");
    getStaticParam(&mNoticeMaskState_s, "NoticeMaskState");
}

void HornUse::calc_() {
    HornUseBase::calc_();
}

}  // namespace uking::action
