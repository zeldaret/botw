#include "Game/Actor/Action/actionPriestBossShadowCloneVanish.h"

namespace uking::action {

PriestBossShadowCloneVanish::PriestBossShadowCloneVanish(const InitArg& arg)
    : PriestBossCloneFastWarp(arg) {}

PriestBossShadowCloneVanish::~PriestBossShadowCloneVanish() = default;

bool PriestBossShadowCloneVanish::init_(sead::Heap* heap) {
    return PriestBossCloneFastWarp::init_(heap);
}

void PriestBossShadowCloneVanish::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossCloneFastWarp::enter_(params);
}

void PriestBossShadowCloneVanish::leave_() {
    PriestBossCloneFastWarp::leave_();
}

void PriestBossShadowCloneVanish::loadParams_() {
    PriestBossCloneFastWarp::loadParams_();
    getStaticParam(&mDelayFrames_s, "DelayFrames");
}

void PriestBossShadowCloneVanish::calc_() {
    PriestBossCloneFastWarp::calc_();
}

}  // namespace uking::action
