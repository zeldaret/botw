#include "Game/Actor/Action/actionPriestBossCloneFastWarp.h"

namespace uking::action {

PriestBossCloneFastWarp::PriestBossCloneFastWarp(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PriestBossCloneFastWarp::~PriestBossCloneFastWarp() = default;

bool PriestBossCloneFastWarp::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PriestBossCloneFastWarp::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void PriestBossCloneFastWarp::leave_() {
    ksys::act::ai::Action::leave_();
}

void PriestBossCloneFastWarp::loadParams_() {
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

void PriestBossCloneFastWarp::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
