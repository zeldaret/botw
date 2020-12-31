#include "Game/AI/AI/aiAnimalAttackOtherTarget.h"

namespace uking::ai {

AnimalAttackOtherTarget::AnimalAttackOtherTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AnimalAttackOtherTarget::~AnimalAttackOtherTarget() = default;

bool AnimalAttackOtherTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AnimalAttackOtherTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void AnimalAttackOtherTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AnimalAttackOtherTarget::loadParams_() {}

}  // namespace uking::ai
