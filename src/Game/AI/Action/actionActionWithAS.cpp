#include "Game/AI/Action/actionActionWithAS.h"

namespace uking::action {

ActionWithAS::ActionWithAS(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

ActionWithAS::~ActionWithAS() = default;

bool ActionWithAS::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void ActionWithAS::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
}

void ActionWithAS::leave_() {
    ActionWithPosAngReduce::leave_();
}

void ActionWithAS::loadParams_() {
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mAngReduceRatio_s, "AngReduceRatio");
}

void ActionWithAS::calc_() {
    ActionWithPosAngReduce::calc_();
}

}  // namespace uking::action
