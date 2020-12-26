#include "Game/AI/Action/actionPlayerEmitEquipmentNoise.h"

namespace uking::action {

PlayerEmitEquipmentNoise::PlayerEmitEquipmentNoise(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

PlayerEmitEquipmentNoise::~PlayerEmitEquipmentNoise() = default;

bool PlayerEmitEquipmentNoise::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PlayerEmitEquipmentNoise::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void PlayerEmitEquipmentNoise::leave_() {
    ksys::act::ai::Action::leave_();
}

void PlayerEmitEquipmentNoise::loadParams_() {
    getDynamicParam(&mSteppingFoot_d, "SteppingFoot");
    getDynamicParam(&mSpeed_d, "Speed");
}

void PlayerEmitEquipmentNoise::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
