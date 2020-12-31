#include "Game/AI/AI/aiJumpAttack.h"

namespace uking::ai {

JumpAttack::JumpAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void JumpAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void JumpAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void JumpAttack::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
