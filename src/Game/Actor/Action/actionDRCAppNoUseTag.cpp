#include "Game/Actor/Action/actionDRCAppNoUseTag.h"

namespace uking::action {

DRCAppNoUseTag::DRCAppNoUseTag(const InitArg& arg) : BasicSignalForbidTag(arg) {}

DRCAppNoUseTag::~DRCAppNoUseTag() = default;

bool DRCAppNoUseTag::init_(sead::Heap* heap) {
    return BasicSignalForbidTag::init_(heap);
}

void DRCAppNoUseTag::enter_(ksys::act::ai::InlineParamPack* params) {
    BasicSignalForbidTag::enter_(params);
}

void DRCAppNoUseTag::leave_() {
    BasicSignalForbidTag::leave_();
}

void DRCAppNoUseTag::loadParams_() {
    BasicSignalForbidTag::loadParams_();
    getMapUnitParam(&mDRCAppNoUseCause_m, "DRCAppNoUseCause");
}

void DRCAppNoUseTag::calc_() {
    BasicSignalForbidTag::calc_();
}

}  // namespace uking::action
