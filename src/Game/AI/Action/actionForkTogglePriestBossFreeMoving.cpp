#include "Game/AI/Action/actionForkTogglePriestBossFreeMoving.h"

namespace uking::action {

ForkTogglePriestBossFreeMoving::ForkTogglePriestBossFreeMoving(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkTogglePriestBossFreeMoving::~ForkTogglePriestBossFreeMoving() = default;

bool ForkTogglePriestBossFreeMoving::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkTogglePriestBossFreeMoving::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkTogglePriestBossFreeMoving::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkTogglePriestBossFreeMoving::loadParams_() {
    getStaticParam(&mSetFreeMoving_s, "SetFreeMoving");
}

void ForkTogglePriestBossFreeMoving::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
