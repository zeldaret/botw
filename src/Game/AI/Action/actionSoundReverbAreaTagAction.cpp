#include "Game/AI/Action/actionSoundReverbAreaTagAction.h"

namespace uking::action {

SoundReverbAreaTagAction::SoundReverbAreaTagAction(const InitArg& arg) : AreaTagAction(arg) {}

SoundReverbAreaTagAction::~SoundReverbAreaTagAction() = default;

bool SoundReverbAreaTagAction::init_(sead::Heap* heap) {
    return AreaTagAction::init_(heap);
}

void SoundReverbAreaTagAction::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaTagAction::enter_(params);
}

void SoundReverbAreaTagAction::leave_() {
    AreaTagAction::leave_();
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
    AreaTagAction::calc_();
}

}  // namespace uking::action
