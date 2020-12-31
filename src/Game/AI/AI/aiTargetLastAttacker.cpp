#include "Game/AI/AI/aiTargetLastAttacker.h"

namespace uking::ai {

TargetLastAttacker::TargetLastAttacker(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetLastAttacker::~TargetLastAttacker() = default;

bool TargetLastAttacker::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetLastAttacker::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TargetLastAttacker::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetLastAttacker::loadParams_() {
    getStaticParam(&mOnEnterOnly_s, "OnEnterOnly");
}

}  // namespace uking::ai
