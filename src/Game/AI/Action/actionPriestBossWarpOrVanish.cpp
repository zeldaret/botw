#include "Game/AI/Action/actionPriestBossWarpOrVanish.h"

namespace uking::action {

PriestBossWarpOrVanish::PriestBossWarpOrVanish(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PriestBossWarpOrVanish::~PriestBossWarpOrVanish() = default;

bool PriestBossWarpOrVanish::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PriestBossWarpOrVanish::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void PriestBossWarpOrVanish::leave_() {
    ksys::act::ai::Action::leave_();
}

void PriestBossWarpOrVanish::loadParams_() {
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

void PriestBossWarpOrVanish::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
