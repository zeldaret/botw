#include "Game/AI/Action/actionForkASTrgTurnGround.h"

namespace uking::action {

ForkASTrgTurnGround::ForkASTrgTurnGround(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkASTrgTurnGround::~ForkASTrgTurnGround() = default;

bool ForkASTrgTurnGround::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkASTrgTurnGround::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkASTrgTurnGround::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkASTrgTurnGround::loadParams_() {
    getStaticParam(&mSpeedBasePosRatio_s, "SpeedBasePosRatio");
    getStaticParam(&mOnAfterGroundRotAngle_s, "OnAfterGroundRotAngle");
    getStaticParam(&mAxis_s, "Axis");
    getStaticParam(&mCtrlOffset_s, "CtrlOffset");
    getStaticParam(&mCtrlAngleOffset_s, "CtrlAngleOffset");
    getStaticParam(&mActMoveVec_s, "ActMoveVec");
    getAITreeVariable(&mCRBOffsetUnit_a, "CRBOffsetUnit");
}

void ForkASTrgTurnGround::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
