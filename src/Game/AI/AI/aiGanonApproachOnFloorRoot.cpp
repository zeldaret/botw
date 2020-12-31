#include "Game/AI/AI/aiGanonApproachOnFloorRoot.h"

namespace uking::ai {

GanonApproachOnFloorRoot::GanonApproachOnFloorRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonApproachOnFloorRoot::~GanonApproachOnFloorRoot() = default;

bool GanonApproachOnFloorRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonApproachOnFloorRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GanonApproachOnFloorRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GanonApproachOnFloorRoot::loadParams_() {
    getStaticParam(&mFinDist_s, "FinDist");
    getStaticParam(&mApproachTime_s, "ApproachTime");
    getStaticParam(&mFinFarDist_s, "FinFarDist");
    getStaticParam(&mMoveFrontRate_s, "MoveFrontRate");
    getStaticParam(&mMoveFrontLRRate_s, "MoveFrontLRRate");
    getStaticParam(&mMoveBackLRRate_s, "MoveBackLRRate");
    getStaticParam(&mCloseDist_s, "CloseDist");
    getStaticParam(&mForbitAngMin_s, "ForbitAngMin");
    getStaticParam(&mForbitAngMax_s, "ForbitAngMax");
    getStaticParam(&mCheckPosAng0_s, "CheckPosAng0");
    getStaticParam(&mCheckPosAng1_s, "CheckPosAng1");
    getStaticParam(&mCheckPosAng2_s, "CheckPosAng2");
    getStaticParam(&mCheckPosAng3_s, "CheckPosAng3");
    getStaticParam(&mCheckPosAng4_s, "CheckPosAng4");
    getDynamicParam(&mIsMoveSide_d, "IsMoveSide");
    getDynamicParam(&mIsChangeable_d, "IsChangeable");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mMoveDstPos_d, "MoveDstPos");
}

}  // namespace uking::ai
