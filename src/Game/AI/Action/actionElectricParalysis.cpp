#include "Game/AI/Action/actionElectricParalysis.h"

namespace uking::action {

ElectricParalysis::ElectricParalysis(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

ElectricParalysis::~ElectricParalysis() = default;

bool ElectricParalysis::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void ElectricParalysis::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
}

void ElectricParalysis::leave_() {
    ActionWithPosAngReduce::leave_();
}

void ElectricParalysis::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void ElectricParalysis::calc_() {
    ActionWithPosAngReduce::calc_();
}

}  // namespace uking::action
