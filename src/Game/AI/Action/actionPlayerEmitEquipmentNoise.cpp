#include "Game/AI/Action/actionPlayerEmitEquipmentNoise.h"

namespace uking::action {

PlayerEmitEquipmentNoise::PlayerEmitEquipmentNoise(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

PlayerEmitEquipmentNoise::~PlayerEmitEquipmentNoise() = default;

bool PlayerEmitEquipmentNoise::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PlayerEmitEquipmentNoise::loadParams_() {
    getDynamicParam(&mSteppingFoot_d, "SteppingFoot");
    getDynamicParam(&mSpeed_d, "Speed");
}

}  // namespace uking::action
