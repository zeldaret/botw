#include "Game/AI/AI/aiSwitchTorch.h"

namespace uking::ai {

SwitchTorch::SwitchTorch(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SwitchTorch::~SwitchTorch() = default;

bool SwitchTorch::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SwitchTorch::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SwitchTorch::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SwitchTorch::loadParams_() {
    getMapUnitParam(&mSwitchTorchSpType_m, "SwitchTorchSpType");
}

}  // namespace uking::ai
