#include "Game/AI/AI/aiReflectableBulletThrown.h"

namespace uking::ai {

ReflectableBulletThrown::ReflectableBulletThrown(const InitArg& arg) : ReflectableThrown(arg) {}

ReflectableBulletThrown::~ReflectableBulletThrown() = default;

bool ReflectableBulletThrown::init_(sead::Heap* heap) {
    return ReflectableThrown::init_(heap);
}

void ReflectableBulletThrown::enter_(ksys::act::ai::InlineParamPack* params) {
    ReflectableThrown::enter_(params);
}

void ReflectableBulletThrown::leave_() {
    ReflectableThrown::leave_();
}

void ReflectableBulletThrown::loadParams_() {
    ReflectableThrown::loadParams_();
    getDynamicParam(&mPower_d, "Power");
    getDynamicParam(&mIsShootByPlayer_d, "IsShootByPlayer");
    getDynamicParam(&mTargetDir_d, "TargetDir");
    getStaticParam(&mReclectSpd_s, "ReclectSpd");
}

}  // namespace uking::ai
