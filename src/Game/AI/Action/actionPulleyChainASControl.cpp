#include "Game/AI/Action/actionPulleyChainASControl.h"

namespace uking::action {

PulleyChainASControl::PulleyChainASControl(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PulleyChainASControl::~PulleyChainASControl() = default;

bool PulleyChainASControl::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PulleyChainASControl::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void PulleyChainASControl::leave_() {
    ksys::act::ai::Action::leave_();
}

void PulleyChainASControl::loadParams_() {
    getStaticParam(&mTargetIdx_s, "TargetIdx");
    getStaticParam(&mSeqBankIdx_s, "SeqBankIdx");
    getStaticParam(&mASName_s, "ASName");
}

void PulleyChainASControl::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
