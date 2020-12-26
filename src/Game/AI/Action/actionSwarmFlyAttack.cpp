#include "Game/AI/Action/actionSwarmFlyAttack.h"

namespace uking::action {

SwarmFlyAttack::SwarmFlyAttack(const InitArg& arg) : SwarmFlyMove(arg) {}

SwarmFlyAttack::~SwarmFlyAttack() = default;

bool SwarmFlyAttack::init_(sead::Heap* heap) {
    return SwarmFlyMove::init_(heap);
}

void SwarmFlyAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    SwarmFlyMove::enter_(params);
}

void SwarmFlyAttack::leave_() {
    SwarmFlyMove::leave_();
}

void SwarmFlyAttack::loadParams_() {
    SwarmFlyMove::loadParams_();
    getStaticParam(&mFailTimeInClosePos_s, "FailTimeInClosePos");
    getStaticParam(&mApplyMaterialAnimNumPerFrame_s, "ApplyMaterialAnimNumPerFrame");
    getStaticParam(&mApplyMaterialAnimDist_s, "ApplyMaterialAnimDist");
}

void SwarmFlyAttack::calc_() {
    SwarmFlyMove::calc_();
}

}  // namespace uking::action
