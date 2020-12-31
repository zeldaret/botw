#include "Game/AI/AI/aiSignalFlowchartRootAI.h"

namespace uking::ai {

SignalFlowchartRootAI::SignalFlowchartRootAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SignalFlowchartRootAI::~SignalFlowchartRootAI() = default;

bool SignalFlowchartRootAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SignalFlowchartRootAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SignalFlowchartRootAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SignalFlowchartRootAI::loadParams_() {
    getMapUnitParam(&mEventFlowName_m, "EventFlowName");
    getMapUnitParam(&mEventFlowEntryName_m, "EventFlowEntryName");
}

}  // namespace uking::ai
