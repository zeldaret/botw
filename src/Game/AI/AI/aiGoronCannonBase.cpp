#include "Game/AI/AI/aiGoronCannonBase.h"

namespace uking::ai {

GoronCannonBase::GoronCannonBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GoronCannonBase::~GoronCannonBase() = default;

bool GoronCannonBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GoronCannonBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GoronCannonBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GoronCannonBase::loadParams_() {
    getStaticParam(&mRotRadAccel_s, "RotRadAccel");
    getStaticParam(&mRotBrake_s, "RotBrake");
    getStaticParam(&mShotCannonBallScale_s, "ShotCannonBallScale");
    getStaticParam(&mIsDrawDebug_s, "IsDrawDebug");
    getStaticParam(&mIsUseShotNodeAngle_s, "IsUseShotNodeAngle");
    getStaticParam(&mActName_s, "ActName");
    getStaticParam(&mShotNodeName_s, "ShotNodeName");
    getStaticParam(&mOffset_s, "Offset");
    getMapUnitParam(&mTiltAngle_m, "TiltAngle");
    getMapUnitParam(&mTiltAngularSpeed_m, "TiltAngularSpeed");
    getMapUnitParam(&mAngle_m, "Angle");
    getMapUnitParam(&mSpeed_m, "Speed");
    getMapUnitParam(&mActorName_m, "ActorName");
}

}  // namespace uking::ai
