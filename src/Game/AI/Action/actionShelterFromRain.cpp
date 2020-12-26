#include "Game/AI/Action/actionShelterFromRain.h"

namespace uking::action {

ShelterFromRain::ShelterFromRain(const InitArg& arg) : AreaTagAction(arg) {}

ShelterFromRain::~ShelterFromRain() = default;

bool ShelterFromRain::init_(sead::Heap* heap) {
    return AreaTagAction::init_(heap);
}

void ShelterFromRain::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaTagAction::enter_(params);
}

void ShelterFromRain::leave_() {
    AreaTagAction::leave_();
}

void ShelterFromRain::loadParams_() {
    getMapUnitParam(&mShelterFromRainTagType_m, "ShelterFromRainTagType");
}

void ShelterFromRain::calc_() {
    AreaTagAction::calc_();
}

}  // namespace uking::action
