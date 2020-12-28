#include "Game/AI/Action/actionHuntingDead.h"

namespace uking::action {

HuntingDead::HuntingDead(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HuntingDead::~HuntingDead() = default;

void HuntingDead::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void HuntingDead::leave_() {
    ksys::act::ai::Action::leave_();
}

void HuntingDead::loadParams_() {
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mIsUseOffsetY_s, "IsUseOffsetY");
    getStaticParam(&mOffsetBoneName_s, "OffsetBoneName");
    getStaticParam(&mExtraOffset_s, "ExtraOffset");
}

void HuntingDead::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
