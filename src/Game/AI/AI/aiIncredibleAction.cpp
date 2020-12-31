#include "Game/AI/AI/aiIncredibleAction.h"

namespace uking::ai {

IncredibleAction::IncredibleAction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

IncredibleAction::~IncredibleAction() = default;

bool IncredibleAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void IncredibleAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void IncredibleAction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void IncredibleAction::loadParams_() {
    getStaticParam(&mIsInvincible_s, "IsInvincible");
    getStaticParam(&mIsUnmoving_s, "IsUnmoving");
    getStaticParam(&mIsNoCollide_s, "IsNoCollide");
    getStaticParam(&mIsUseIncredibleActionDCCallback_s, "IsUseIncredibleActionDCCallback");
}

}  // namespace uking::ai
