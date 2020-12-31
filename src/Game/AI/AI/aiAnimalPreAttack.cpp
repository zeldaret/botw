#include "Game/AI/AI/aiAnimalPreAttack.h"

namespace uking::ai {

AnimalPreAttack::AnimalPreAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AnimalPreAttack::~AnimalPreAttack() = default;

bool AnimalPreAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AnimalPreAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void AnimalPreAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AnimalPreAttack::loadParams_() {
    getStaticParam(&mForceEndTime_s, "ForceEndTime");
    getStaticParam(&mKeepDistCheckLength_s, "KeepDistCheckLength");
    getStaticParam(&mBackCliffCheckLength_s, "BackCliffCheckLength");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
