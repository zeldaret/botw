#include "Game/AI/Action/actionTeleportForceApperPosition.h"

namespace uking::action {

TeleportForceApperPosition::TeleportForceApperPosition(const InitArg& arg) : TeleportBase(arg) {}

TeleportForceApperPosition::~TeleportForceApperPosition() = default;

bool TeleportForceApperPosition::init_(sead::Heap* heap) {
    return TeleportBase::init_(heap);
}

void TeleportForceApperPosition::enter_(ksys::act::ai::InlineParamPack* params) {
    TeleportBase::enter_(params);
}

void TeleportForceApperPosition::leave_() {
    TeleportBase::leave_();
}

void TeleportForceApperPosition::loadParams_() {
    TeleportBase::loadParams_();
    getStaticParam(&mArriveAtTargetTimeOut_s, "ArriveAtTargetTimeOut");
    getStaticParam(&mArriveAtTargetRange_s, "ArriveAtTargetRange");
    getStaticParam(&mIsArriveAtTarget_s, "IsArriveAtTarget");
    getStaticParam(&mHideEffectName_s, "HideEffectName");
    getDynamicParam(&mAppearPosition_d, "AppearPosition");
}

void TeleportForceApperPosition::calc_() {
    TeleportBase::calc_();
}

}  // namespace uking::action
