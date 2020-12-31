#include "Game/AI/AI/aiRemainElectricCannonBeamAttack.h"

namespace uking::ai {

RemainElectricCannonBeamAttack::RemainElectricCannonBeamAttack(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

RemainElectricCannonBeamAttack::~RemainElectricCannonBeamAttack() = default;

bool RemainElectricCannonBeamAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RemainElectricCannonBeamAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RemainElectricCannonBeamAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RemainElectricCannonBeamAttack::loadParams_() {}

}  // namespace uking::ai
