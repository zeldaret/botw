#include "Game/Actor/Action/actionHornUse.h"

namespace uking::action {

HornUse::HornUse(const InitArg& arg) : EquipHornUseBase(arg) {}

HornUse::~HornUse() = default;

bool HornUse::init_(sead::Heap* heap) {
    return EquipHornUseBase::init_(heap);
}

void HornUse::enter_(ksys::act::ai::InlineParamPack* params) {
    EquipHornUseBase::enter_(params);
}

void HornUse::leave_() {
    EquipHornUseBase::leave_();
}

void HornUse::loadParams_() {
    EquipHornUseBase::loadParams_();
    getStaticParam(&mSpreadDist_s, "SpreadDist");
    getStaticParam(&mSpreadTime_s, "SpreadTime");
    getStaticParam(&mTerrorLevel_s, "TerrorLevel");
    getStaticParam(&mNoticeMaskState_s, "NoticeMaskState");
}

void HornUse::calc_() {
    EquipHornUseBase::calc_();
}

}  // namespace uking::action
