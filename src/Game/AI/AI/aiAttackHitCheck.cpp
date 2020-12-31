#include "Game/AI/AI/aiAttackHitCheck.h"

namespace uking::ai {

AttackHitCheck::AttackHitCheck(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AttackHitCheck::~AttackHitCheck() = default;

bool AttackHitCheck::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AttackHitCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void AttackHitCheck::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AttackHitCheck::loadParams_() {
    getStaticParam(&mAtkType_s, "AtkType");
}

}  // namespace uking::ai
