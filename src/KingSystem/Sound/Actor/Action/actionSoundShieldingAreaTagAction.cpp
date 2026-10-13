#include "KingSystem/Sound/Actor/Action/actionSoundShieldingAreaTagAction.h"

namespace ksys::snd {

SoundShieldingAreaTagAction::SoundShieldingAreaTagAction(const InitArg& arg)
    : AreaActionBase(arg) {}

SoundShieldingAreaTagAction::~SoundShieldingAreaTagAction() = default;

bool SoundShieldingAreaTagAction::init_(sead::Heap* heap) {
    return AreaActionBase::init_(heap);
}

void SoundShieldingAreaTagAction::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaActionBase::enter_(params);
}

void SoundShieldingAreaTagAction::leave_() {
    AreaActionBase::leave_();
}

void SoundShieldingAreaTagAction::loadParams_() {
    getMapUnitParam(&mMerginDistance_m, "MerginDistance");
    getMapUnitParam(&mIsShieldChemicalWind_m, "IsShieldChemicalWind");
}

void SoundShieldingAreaTagAction::calc_() {
    AreaActionBase::calc_();
}

}  // namespace ksys::snd
