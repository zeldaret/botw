#include "Game/AI/AI/aiPriestBossFastWarpAttack.h"

namespace uking::ai {

PriestBossFastWarpAttack::PriestBossFastWarpAttack(const InitArg& arg)
    : SiteBossSwordApproachRoot(arg) {}

PriestBossFastWarpAttack::~PriestBossFastWarpAttack() = default;

bool PriestBossFastWarpAttack::init_(sead::Heap* heap) {
    return SiteBossSwordApproachRoot::init_(heap);
}

void PriestBossFastWarpAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossSwordApproachRoot::enter_(params);
}

void PriestBossFastWarpAttack::leave_() {
    SiteBossSwordApproachRoot::leave_();
}

void PriestBossFastWarpAttack::loadParams_() {
    SiteBossSwordApproachRoot::loadParams_();
}

}  // namespace uking::ai
