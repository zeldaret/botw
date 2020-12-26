#include "Game/AI/Action/actionBrightBowSlowFall.h"

namespace uking::action {

BrightBowSlowFall::BrightBowSlowFall(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BrightBowSlowFall::~BrightBowSlowFall() = default;

bool BrightBowSlowFall::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BrightBowSlowFall::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BrightBowSlowFall::leave_() {
    ksys::act::ai::Action::leave_();
}

void BrightBowSlowFall::loadParams_() {
    getStaticParam(&mGravity_s, "Gravity");
    getStaticParam(&mFloatWaveCycle_s, "FloatWaveCycle");
    getStaticParam(&mFloatWaveWidth_s, "FloatWaveWidth");
    getStaticParam(&mFloatHeight_s, "FloatHeight");
    getStaticParam(&mFloatSpring_s, "FloatSpring");
    getStaticParam(&mFloatDamper_s, "FloatDamper");
    getStaticParam(&mFallBrakeHeight_s, "FallBrakeHeight");
    getStaticParam(&mFallBrake_s, "FallBrake");
    getStaticParam(&mAttractionRange_s, "AttractionRange");
    getStaticParam(&mAttractionRate_s, "AttractionRate");
    getStaticParam(&mTailEffectKeyName_s, "TailEffectKeyName");
    getStaticParam(&mInitRotate_s, "InitRotate");
    getStaticParam(&mRotateSpeed_s, "RotateSpeed");
}

void BrightBowSlowFall::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
