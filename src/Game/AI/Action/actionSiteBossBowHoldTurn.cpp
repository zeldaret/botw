#include "Game/AI/Action/actionSiteBossBowHoldTurn.h"

namespace uking::action {

SiteBossBowHoldTurn::SiteBossBowHoldTurn(const InitArg& arg) : TurnBase(arg) {}

SiteBossBowHoldTurn::~SiteBossBowHoldTurn() = default;

bool SiteBossBowHoldTurn::init_(sead::Heap* heap) {
    return TurnBase::init_(heap);
}

void SiteBossBowHoldTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    TurnBase::enter_(params);
}

void SiteBossBowHoldTurn::leave_() {
    TurnBase::leave_();
}

void SiteBossBowHoldTurn::loadParams_() {
    TurnBase::loadParams_();
    getStaticParam(&mSpineControlOffsetAngleLR_s, "SpineControlOffsetAngleLR");
    getStaticParam(&mSpineControlOffsetAngleUD_s, "SpineControlOffsetAngleUD");
    getStaticParam(&mASName_s, "ASName");
}

void SiteBossBowHoldTurn::calc_() {
    TurnBase::calc_();
}

}  // namespace uking::action
