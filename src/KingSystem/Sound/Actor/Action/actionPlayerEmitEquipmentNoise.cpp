#include "KingSystem/Sound/Actor/Action/actionPlayerEmitEquipmentNoise.h"

namespace ksys::snd {

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

}  // namespace ksys::snd
