#include "Game/AI/Action/actionReflectThrown.h"

namespace uking::action {

ReflectThrown::ReflectThrown(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ReflectThrown::~ReflectThrown() = default;

bool ReflectThrown::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ReflectThrown::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ReflectThrown::leave_() {
    ksys::act::ai::Action::leave_();
}

void ReflectThrown::loadParams_() {
    getStaticParam(&mReactionLevel_s, "ReactionLevel");
    getStaticParam(&mFinishWaterDepth_s, "FinishWaterDepth");
    getDynamicParam(&mPower_d, "Power");
    getDynamicParam(&mTargetDir_d, "TargetDir");
    getAITreeVariable(&mIsReflectThrownBullet_a, "IsReflectThrownBullet");
}

void ReflectThrown::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
