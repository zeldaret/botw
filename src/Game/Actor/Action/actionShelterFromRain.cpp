#include "Game/Actor/Action/actionShelterFromRain.h"

namespace uking::action {

ShelterFromRain::ShelterFromRain(const InitArg& arg) : AreaActionBase(arg) {}

ShelterFromRain::~ShelterFromRain() = default;

bool ShelterFromRain::init_(sead::Heap* heap) {
    return AreaActionBase::init_(heap);
}

void ShelterFromRain::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaActionBase::enter_(params);
}

void ShelterFromRain::leave_() {
    AreaActionBase::leave_();
}

void ShelterFromRain::loadParams_() {
    getMapUnitParam(&mShelterFromRainTagType_m, "ShelterFromRainTagType");
}

void ShelterFromRain::calc_() {
    AreaActionBase::calc_();
}

}  // namespace uking::action
