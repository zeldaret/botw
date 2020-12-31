#include "Game/AI/AI/aiAnimalEscapeAfterDamage.h"

namespace uking::ai {

AnimalEscapeAfterDamage::AnimalEscapeAfterDamage(const InitArg& arg) : AnimalEscapeAI(arg) {}

AnimalEscapeAfterDamage::~AnimalEscapeAfterDamage() = default;

bool AnimalEscapeAfterDamage::init_(sead::Heap* heap) {
    return AnimalEscapeAI::init_(heap);
}

void AnimalEscapeAfterDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalEscapeAI::enter_(params);
}

void AnimalEscapeAfterDamage::leave_() {
    AnimalEscapeAI::leave_();
}

void AnimalEscapeAfterDamage::loadParams_() {
    AnimalEscapeAI::loadParams_();
}

}  // namespace uking::ai
