#include "Game/AI/Action/actionSoundOcclusionTagRemainsWater.h"

namespace uking::action {

SoundOcclusionTagRemainsWater::SoundOcclusionTagRemainsWater(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SoundOcclusionTagRemainsWater::~SoundOcclusionTagRemainsWater() = default;

bool SoundOcclusionTagRemainsWater::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SoundOcclusionTagRemainsWater::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SoundOcclusionTagRemainsWater::leave_() {
    ksys::act::ai::Action::leave_();
}

void SoundOcclusionTagRemainsWater::loadParams_() {}

void SoundOcclusionTagRemainsWater::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
