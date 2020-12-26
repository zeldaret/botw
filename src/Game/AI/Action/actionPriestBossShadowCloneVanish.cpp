#include "Game/AI/Action/actionPriestBossShadowCloneVanish.h"

namespace uking::action {

PriestBossShadowCloneVanish::PriestBossShadowCloneVanish(const InitArg& arg)
    : PriestBossWarpOrVanish(arg) {}

PriestBossShadowCloneVanish::~PriestBossShadowCloneVanish() = default;

bool PriestBossShadowCloneVanish::init_(sead::Heap* heap) {
    return PriestBossWarpOrVanish::init_(heap);
}

void PriestBossShadowCloneVanish::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossWarpOrVanish::enter_(params);
}

void PriestBossShadowCloneVanish::leave_() {
    PriestBossWarpOrVanish::leave_();
}

void PriestBossShadowCloneVanish::loadParams_() {
    PriestBossWarpOrVanish::loadParams_();
    getStaticParam(&mDelayFrames_s, "DelayFrames");
}

void PriestBossShadowCloneVanish::calc_() {
    PriestBossWarpOrVanish::calc_();
}

}  // namespace uking::action
