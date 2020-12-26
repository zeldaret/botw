#include "Game/AI/Action/actionDRCAppNoUseTag.h"

namespace uking::action {

DRCAppNoUseTag::DRCAppNoUseTag(const InitArg& arg) : ForbidTag(arg) {}

DRCAppNoUseTag::~DRCAppNoUseTag() = default;

bool DRCAppNoUseTag::init_(sead::Heap* heap) {
    return ForbidTag::init_(heap);
}

void DRCAppNoUseTag::enter_(ksys::act::ai::InlineParamPack* params) {
    ForbidTag::enter_(params);
}

void DRCAppNoUseTag::leave_() {
    ForbidTag::leave_();
}

void DRCAppNoUseTag::loadParams_() {
    ForbidTag::loadParams_();
    getMapUnitParam(&mDRCAppNoUseCause_m, "DRCAppNoUseCause");
}

void DRCAppNoUseTag::calc_() {
    ForbidTag::calc_();
}

}  // namespace uking::action
