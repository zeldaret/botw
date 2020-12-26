#include "Game/AI/Action/actionNPCTebaApproachPlayer.h"

namespace uking::action {

NPCTebaApproachPlayer::NPCTebaApproachPlayer(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCTebaApproachPlayer::~NPCTebaApproachPlayer() = default;

bool NPCTebaApproachPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCTebaApproachPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCTebaApproachPlayer::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCTebaApproachPlayer::loadParams_() {
    getStaticParam(&mUpdateTargetFrame_s, "UpdateTargetFrame");
    getStaticParam(&mPlayerMaxHeight_s, "PlayerMaxHeight");
    getStaticParam(&mMaxMoveSpeed_s, "MaxMoveSpeed");
    getStaticParam(&mTurnSpeed_s, "TurnSpeed");
    getStaticParam(&mTurnRadius_s, "TurnRadius");
    getStaticParam(&mReduceMaxSpeedChasePlayer_s, "ReduceMaxSpeedChasePlayer");
}

void NPCTebaApproachPlayer::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
