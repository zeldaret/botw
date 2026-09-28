#include "Game/Actor/Action/actionBalloonRopeBase.h"

namespace uking::action {

BalloonRopeBase::BalloonRopeBase(const InitArg& arg) : BalloonBase(arg) {}

BalloonRopeBase::~BalloonRopeBase() = default;

bool BalloonRopeBase::init_(sead::Heap* heap) {
    return BalloonBase::init_(heap);
}

void BalloonRopeBase::enter_(ksys::act::ai::InlineParamPack* params) {
    BalloonBase::enter_(params);
}

void BalloonRopeBase::leave_() {
    BalloonBase::leave_();
}

void BalloonRopeBase::loadParams_() {
    BalloonBase::loadParams_();
    getStaticParam(&mConnectReleaseTimer_s, "ConnectReleaseTimer");
    getStaticParam(&mClampWindForceScale_s, "ClampWindForceScale");
    getStaticParam(&mReduceVel_s, "ReduceVel");
    getDynamicParam(&mConnectRigidName_d, "ConnectRigidName");
    getDynamicParam(&mConnectRigidOffset_d, "ConnectRigidOffset");
    getDynamicParam(&mRopeActorHandle_d, "RopeActorHandle");
}

void BalloonRopeBase::calc_() {
    BalloonBase::calc_();
}

}  // namespace uking::action
