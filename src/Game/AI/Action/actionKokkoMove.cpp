#include "Game/AI/Action/actionKokkoMove.h"

namespace uking::action {

KokkoMove::KokkoMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

KokkoMove::~KokkoMove() = default;

bool KokkoMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void KokkoMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void KokkoMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void KokkoMove::loadParams_() {
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mAngularSpeed_s, "AngularSpeed");
    getStaticParam(&mNavMeshGoalDistanceTolerance_s, "NavMeshGoalDistanceTolerance");
    getStaticParam(&mIsIgnoreSameAS_s, "IsIgnoreSameAS");
    getStaticParam(&mIsCancelRequestedPathFirst_s, "IsCancelRequestedPathFirst");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mAvoidPlayer_s, "AvoidPlayer");
    getStaticParam(&mUseLocalSteering_s, "UseLocalSteering");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void KokkoMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
