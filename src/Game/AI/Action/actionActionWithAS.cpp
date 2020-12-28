#include "Game/AI/Action/actionActionWithAS.h"

namespace uking::action {

ActionWithAS::ActionWithAS(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

void ActionWithAS::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
}

void ActionWithAS::calc_() {
    ActionWithPosAngReduce::calc_();
}

}  // namespace uking::action
