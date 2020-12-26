#include "Game/AI/Action/actionForkSetSwarmMaterialAnimByDist.h"

namespace uking::action {

ForkSetSwarmMaterialAnimByDist::ForkSetSwarmMaterialAnimByDist(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkSetSwarmMaterialAnimByDist::~ForkSetSwarmMaterialAnimByDist() = default;

bool ForkSetSwarmMaterialAnimByDist::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkSetSwarmMaterialAnimByDist::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkSetSwarmMaterialAnimByDist::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkSetSwarmMaterialAnimByDist::loadParams_() {
    getStaticParam(&mApplyMaterialAnimNumPerFrame_s, "ApplyMaterialAnimNumPerFrame");
    getStaticParam(&mSetState_s, "SetState");
    getStaticParam(&mApplyMaterialAnimDist_s, "ApplyMaterialAnimDist");
    getStaticParam(&mMaterialAnimFrame_s, "MaterialAnimFrame");
    getStaticParam(&mMaterialAnimName_s, "MaterialAnimName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void ForkSetSwarmMaterialAnimByDist::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
