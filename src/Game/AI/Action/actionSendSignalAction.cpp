#include "Game/AI/Action/actionSendSignalAction.h"

namespace uking::action {

SendSignalAction::SendSignalAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SendSignalAction::~SendSignalAction() = default;

bool SendSignalAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SendSignalAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SendSignalAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void SendSignalAction::loadParams_() {
    getDynamicParam(&mSignalType_d, "SignalType");
    getDynamicParam(&mValue_d, "Value");
}

void SendSignalAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
