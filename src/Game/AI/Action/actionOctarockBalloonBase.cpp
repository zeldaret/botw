#include "Game/AI/Action/actionOctarockBalloonBase.h"

namespace uking::action {

OctarockBalloonBase::OctarockBalloonBase(const InitArg& arg) : BalloonBase(arg) {}

OctarockBalloonBase::~OctarockBalloonBase() = default;

bool OctarockBalloonBase::init_(sead::Heap* heap) {
    return BalloonBase::init_(heap);
}

void OctarockBalloonBase::enter_(ksys::act::ai::InlineParamPack* params) {
    BalloonBase::enter_(params);
}

void OctarockBalloonBase::leave_() {
    BalloonBase::leave_();
}

void OctarockBalloonBase::loadParams_() {
    BalloonBase::loadParams_();
    getStaticParam(&mConnectReleaseTimer_s, "ConnectReleaseTimer");
    getStaticParam(&mClampWindForceScale_s, "ClampWindForceScale");
    getStaticParam(&mReduceVel_s, "ReduceVel");
    getDynamicParam(&mConnectRigidName_d, "ConnectRigidName");
    getDynamicParam(&mConnectRigidOffset_d, "ConnectRigidOffset");
    getDynamicParam(&mRopeActorHandle_d, "RopeActorHandle");
}

void OctarockBalloonBase::calc_() {
    BalloonBase::calc_();
}

}  // namespace uking::action
