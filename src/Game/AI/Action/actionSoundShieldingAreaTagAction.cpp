#include "Game/AI/Action/actionSoundShieldingAreaTagAction.h"

namespace uking::action {

SoundShieldingAreaTagAction::SoundShieldingAreaTagAction(const InitArg& arg) : AreaTagAction(arg) {}

SoundShieldingAreaTagAction::~SoundShieldingAreaTagAction() = default;

bool SoundShieldingAreaTagAction::init_(sead::Heap* heap) {
    return AreaTagAction::init_(heap);
}

void SoundShieldingAreaTagAction::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaTagAction::enter_(params);
}

void SoundShieldingAreaTagAction::leave_() {
    AreaTagAction::leave_();
}

void SoundShieldingAreaTagAction::loadParams_() {
    getMapUnitParam(&mMerginDistance_m, "MerginDistance");
    getMapUnitParam(&mIsShieldChemicalWind_m, "IsShieldChemicalWind");
}

void SoundShieldingAreaTagAction::calc_() {
    AreaTagAction::calc_();
}

}  // namespace uking::action
