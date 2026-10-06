#include "Game/Actor/AI/aiBigCannon.h"

namespace uking::ai {

BigCannon::BigCannon(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BigCannon::~BigCannon() = default;

bool BigCannon::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void BigCannon::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void BigCannon::leave_() {
    ksys::act::ai::Ai::leave_();
}

void BigCannon::loadParams_() {
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
