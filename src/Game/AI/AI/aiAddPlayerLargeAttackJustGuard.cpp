#include "Game/AI/AI/aiAddPlayerLargeAttackJustGuard.h"

namespace uking::ai {

AddPlayerLargeAttackJustGuard::AddPlayerLargeAttackJustGuard(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

bool AddPlayerLargeAttackJustGuard::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AddPlayerLargeAttackJustGuard::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void AddPlayerLargeAttackJustGuard::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AddPlayerLargeAttackJustGuard::loadParams_() {}

}  // namespace uking::ai
