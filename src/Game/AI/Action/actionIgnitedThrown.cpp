#include "Game/AI/Action/actionIgnitedThrown.h"

namespace uking::action {

IgnitedThrown::IgnitedThrown(const InitArg& arg) : ksys::act::ai::Action(arg) {}

IgnitedThrown::~IgnitedThrown() = default;

bool IgnitedThrown::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void IgnitedThrown::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void IgnitedThrown::leave_() {
    ksys::act::ai::Action::leave_();
}

void IgnitedThrown::loadParams_() {
    getStaticParam(&mReactionLevel_s, "ReactionLevel");
    getStaticParam(&mDamageScale_s, "DamageScale");
    getStaticParam(&mFinishWaterDepth_s, "FinishWaterDepth");
    getStaticParam(&mIsScaling_s, "IsScaling");
    getStaticParam(&mIsFinishedByOneHit_s, "IsFinishedByOneHit");
    getStaticParam(&mIsFadeIn_s, "IsFadeIn");
    getStaticParam(&mIsAbleGuard_s, "IsAbleGuard");
    getStaticParam(&mIsForceOnly_s, "IsForceOnly");
    getStaticParam(&mAS_s, "AS");
}

void IgnitedThrown::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
