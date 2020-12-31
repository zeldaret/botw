#include "Game/AI/AI/aiAttackGrave.h"

namespace uking::ai {

AttackGrave::AttackGrave(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AttackGrave::~AttackGrave() = default;

bool AttackGrave::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AttackGrave::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void AttackGrave::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AttackGrave::loadParams_() {}

}  // namespace uking::ai
