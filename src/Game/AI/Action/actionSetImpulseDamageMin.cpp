#include "Game/AI/Action/actionSetImpulseDamageMin.h"

namespace uking::action {

SetImpulseDamageMin::SetImpulseDamageMin(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetImpulseDamageMin::~SetImpulseDamageMin() = default;

bool SetImpulseDamageMin::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetImpulseDamageMin::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SetImpulseDamageMin::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetImpulseDamageMin::loadParams_() {
    getStaticParam(&mReactionLevel_s, "ReactionLevel");
    getStaticParam(&mIsGuardable_s, "IsGuardable");
    getStaticParam(&mIsGuarantee_s, "IsGuarantee");
}

void SetImpulseDamageMin::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
