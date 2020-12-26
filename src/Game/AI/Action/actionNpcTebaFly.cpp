#include "Game/AI/Action/actionNpcTebaFly.h"

namespace uking::action {

NpcTebaFly::NpcTebaFly(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NpcTebaFly::~NpcTebaFly() = default;

bool NpcTebaFly::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NpcTebaFly::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NpcTebaFly::leave_() {
    ksys::act::ai::Action::leave_();
}

void NpcTebaFly::loadParams_() {
    getStaticParam(&mTurnEnableFrame_s, "TurnEnableFrame");
    getStaticParam(&mStartTurnDist_s, "StartTurnDist");
    getStaticParam(&mTurnSpeed_s, "TurnSpeed");
    getStaticParam(&mInterpolateTurnFrameForMaxSpeed_s, "InterpolateTurnFrameForMaxSpeed");
    getStaticParam(&mInterpolateMoveFrameForMaxSpeed_s, "InterpolateMoveFrameForMaxSpeed");
    getStaticParam(&mTurnEndRad_s, "TurnEndRad");
    getStaticParam(&mMoveSpeedMin_s, "MoveSpeedMin");
    getStaticParam(&mMoveSpeedMax_s, "MoveSpeedMax");
    getStaticParam(&mTurnReduceSpeedRatio_s, "TurnReduceSpeedRatio");
    getStaticParam(&mEvacuateRemainsDist_s, "EvacuateRemainsDist");
    getStaticParam(&mTargetPosRatio_s, "TargetPosRatio");
    getStaticParam(&mPlayerApproachCannonDist_s, "PlayerApproachCannonDist");
}

void NpcTebaFly::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
