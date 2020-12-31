#include "Game/AI/AI/aiAnimalBattleMoveLeave.h"

namespace uking::ai {

AnimalBattleMoveLeave::AnimalBattleMoveLeave(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AnimalBattleMoveLeave::~AnimalBattleMoveLeave() = default;

bool AnimalBattleMoveLeave::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AnimalBattleMoveLeave::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void AnimalBattleMoveLeave::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AnimalBattleMoveLeave::loadParams_() {
    getStaticParam(&mCheckForwardDist_s, "CheckForwardDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
