#include "Game/AI/AI/aiAnimalRushAttack.h"

namespace uking::ai {

AnimalRushAttack::AnimalRushAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AnimalRushAttack::~AnimalRushAttack() = default;

bool AnimalRushAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AnimalRushAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void AnimalRushAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AnimalRushAttack::loadParams_() {
    getStaticParam(&mUpdateTargetPosTime_s, "UpdateTargetPosTime");
    getStaticParam(&mAttackPosOffsetLength_s, "AttackPosOffsetLength");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
