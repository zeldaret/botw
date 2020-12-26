#include "Game/AI/Action/actionSendSignalForSignalFlowAct.h"

namespace uking::action {

SendSignalForSignalFlowAct::SendSignalForSignalFlowAct(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SendSignalForSignalFlowAct::~SendSignalForSignalFlowAct() = default;

bool SendSignalForSignalFlowAct::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SendSignalForSignalFlowAct::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SendSignalForSignalFlowAct::leave_() {
    ksys::act::ai::Action::leave_();
}

void SendSignalForSignalFlowAct::loadParams_() {
    getDynamicParam(&mSignalType_d, "SignalType");
    getDynamicParam(&mValue_d, "Value");
}

void SendSignalForSignalFlowAct::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
