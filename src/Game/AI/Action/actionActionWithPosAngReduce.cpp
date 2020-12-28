#include "Game/AI/Action/actionActionWithPosAngReduce.h"

namespace uking::action {

ActionWithPosAngReduce::ActionWithPosAngReduce(const InitArg& arg) : ActionEx(arg) {}

void ActionWithPosAngReduce::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void ActionWithPosAngReduce::leave_() {
    ActionEx::leave_();
}

void ActionWithPosAngReduce::loadParams_() {
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mAngReduceRatio_s, "AngReduceRatio");
}

void ActionWithPosAngReduce::calc_() {
    ActionEx::calc_();
}

}  // namespace uking::action
