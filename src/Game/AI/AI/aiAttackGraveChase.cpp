#include "Game/AI/AI/aiAttackGraveChase.h"

namespace uking::ai {

AttackGraveChase::AttackGraveChase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AttackGraveChase::~AttackGraveChase() = default;

bool AttackGraveChase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AttackGraveChase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void AttackGraveChase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AttackGraveChase::loadParams_() {
    getStaticParam(&mActionTime_s, "ActionTime");
    getStaticParam(&mNearTime_s, "NearTime");
    getStaticParam(&mEndHeight_s, "EndHeight");
    getStaticParam(&mEndNear_s, "EndNear");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
