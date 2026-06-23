#include "Game/AI/Action/actionActionWithAS.h"

namespace uking::action {

ActionWithAS::ActionWithAS(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

void ActionWithAS::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
}

void ActionWithAS::calc_() {
    ActionWithPosAngReduce::calc_();
}

bool ActionWithAS::isFinished() const {
    return mFlags.isOn(Flag::Finished) || const_cast<ActionWithAS*>(this)->isFinishedAS(0, 0);
}

}  // namespace uking::action
