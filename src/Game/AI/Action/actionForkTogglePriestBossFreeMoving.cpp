#include "Game/AI/Action/actionForkTogglePriestBossFreeMoving.h"

namespace uking::action {

ForkTogglePriestBossFreeMoving::ForkTogglePriestBossFreeMoving(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkTogglePriestBossFreeMoving::~ForkTogglePriestBossFreeMoving() = default;

void ForkTogglePriestBossFreeMoving::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkTogglePriestBossFreeMoving::loadParams_() {
    getStaticParam(&mSetFreeMoving_s, "SetFreeMoving");
}

}  // namespace uking::action
