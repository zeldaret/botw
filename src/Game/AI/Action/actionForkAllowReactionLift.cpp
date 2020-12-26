#include "Game/AI/Action/actionForkAllowReactionLift.h"

namespace uking::action {

ForkAllowReactionLift::ForkAllowReactionLift(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkAllowReactionLift::~ForkAllowReactionLift() = default;

bool ForkAllowReactionLift::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkAllowReactionLift::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkAllowReactionLift::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkAllowReactionLift::loadParams_() {
    getAITreeVariable(&mIsAllowReactionLift_a, "IsAllowReactionLift");
}

void ForkAllowReactionLift::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
