#include "Game/AI/AI/aiPreyChemicalDeadReaction.h"

namespace uking::ai {

PreyChemicalDeadReaction::PreyChemicalDeadReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PreyChemicalDeadReaction::~PreyChemicalDeadReaction() = default;

bool PreyChemicalDeadReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PreyChemicalDeadReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PreyChemicalDeadReaction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PreyChemicalDeadReaction::loadParams_() {}

}  // namespace uking::ai
