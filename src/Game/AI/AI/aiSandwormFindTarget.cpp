#include "Game/AI/AI/aiSandwormFindTarget.h"

namespace uking::ai {

SandwormFindTarget::SandwormFindTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SandwormFindTarget::~SandwormFindTarget() = default;

bool SandwormFindTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SandwormFindTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SandwormFindTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SandwormFindTarget::loadParams_() {
    getStaticParam(&mLostTimer_s, "LostTimer");
    getStaticParam(&mLostVMin_s, "LostVMin");
    getStaticParam(&mLostVMax_s, "LostVMax");
    getStaticParam(&mLostRange_s, "LostRange");
    getStaticParam(&mAttackRange_s, "AttackRange");
}

}  // namespace uking::ai
