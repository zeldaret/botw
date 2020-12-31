#include "Game/AI/AI/aiEnemySittingTogether.h"

namespace uking::ai {

EnemySittingTogether::EnemySittingTogether(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool EnemySittingTogether::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemySittingTogether::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemySittingTogether::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemySittingTogether::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getAITreeVariable(&mIsNextActionReserved_a, "IsNextActionReserved");
}

}  // namespace uking::ai
