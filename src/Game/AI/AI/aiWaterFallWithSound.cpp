#include "Game/AI/AI/aiWaterFallWithSound.h"

namespace uking::ai {

WaterFallWithSound::WaterFallWithSound(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WaterFallWithSound::~WaterFallWithSound() = default;

bool WaterFallWithSound::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WaterFallWithSound::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WaterFallWithSound::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WaterFallWithSound::loadParams_() {}

}  // namespace uking::ai
