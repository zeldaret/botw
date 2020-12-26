#include "Game/AI/Action/actionDieAnm.h"

namespace uking::action {

DieAnm::DieAnm(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

DieAnm::~DieAnm() = default;

bool DieAnm::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void DieAnm::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
}

void DieAnm::leave_() {
    ActionWithPosAngReduce::leave_();
}

void DieAnm::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void DieAnm::calc_() {
    ActionWithPosAngReduce::calc_();
}

}  // namespace uking::action
