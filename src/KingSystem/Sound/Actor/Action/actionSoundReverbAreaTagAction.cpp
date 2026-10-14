#include "KingSystem/Sound/Actor/Action/actionSoundReverbAreaTagAction.h"

namespace ksys::snd {

SoundReverbAreaTagAction::SoundReverbAreaTagAction(const InitArg& arg) : AreaActionBase(arg) {}

SoundReverbAreaTagAction::~SoundReverbAreaTagAction() = default;

bool SoundReverbAreaTagAction::init_(sead::Heap* heap) {
    return AreaActionBase::init_(heap);
}

void SoundReverbAreaTagAction::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaActionBase::enter_(params);
}

void SoundReverbAreaTagAction::leave_() {
    AreaActionBase::leave_();
}

void SoundReverbAreaTagAction::loadParams_() {
    getMapUnitParam(&mReverbSendAdd_m, "ReverbSendAdd");
    getMapUnitParam(&mReverbTimeAdd_m, "ReverbTimeAdd");
    getMapUnitParam(&mEarlyReflectionFeedbackAdd_m, "EarlyReflectionFeedbackAdd");
    getMapUnitParam(&mRoomHfAdd_m, "RoomHfAdd");
    getMapUnitParam(&mReverbAdd_m, "ReverbAdd");
    getMapUnitParam(&mMerginDistance_m, "MerginDistance");
}

void SoundReverbAreaTagAction::calc_() {
    AreaActionBase::calc_();
}

}  // namespace ksys::snd
