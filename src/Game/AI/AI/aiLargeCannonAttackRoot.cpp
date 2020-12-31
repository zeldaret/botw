#include "Game/AI/AI/aiLargeCannonAttackRoot.h"

namespace uking::ai {

LargeCannonAttackRoot::LargeCannonAttackRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LargeCannonAttackRoot::~LargeCannonAttackRoot() = default;

bool LargeCannonAttackRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LargeCannonAttackRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LargeCannonAttackRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LargeCannonAttackRoot::loadParams_() {
    getStaticParam(&mAttackWaitTime_s, "AttackWaitTime");
}

}  // namespace uking::ai
