#include "Game/AI/Action/actionSendSignalForSignalFlowAct.h"

namespace uking::action {

SendSignalForSignalFlowAct::SendSignalForSignalFlowAct(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SendSignalForSignalFlowAct::~SendSignalForSignalFlowAct() = default;

bool SendSignalForSignalFlowAct::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SendSignalForSignalFlowAct::loadParams_() {
    getDynamicParam(&mSignalType_d, "SignalType");
    getDynamicParam(&mValue_d, "Value");
}

}  // namespace uking::action
