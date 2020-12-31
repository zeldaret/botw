#include "Game/AI/AI/aiPillarCrack.h"

namespace uking::ai {

PillarCrack::PillarCrack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PillarCrack::~PillarCrack() = default;

bool PillarCrack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PillarCrack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PillarCrack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PillarCrack::loadParams_() {}

}  // namespace uking::ai
