#include "Game/AI/Action/actionForkBeastGanonMessageDialogCtrl.h"

namespace uking::action {

ForkBeastGanonMessageDialogCtrl::ForkBeastGanonMessageDialogCtrl(const InitArg& arg)
    : SimpleMessageDialogCtrl(arg) {}

ForkBeastGanonMessageDialogCtrl::~ForkBeastGanonMessageDialogCtrl() = default;

bool ForkBeastGanonMessageDialogCtrl::init_(sead::Heap* heap) {
    return SimpleMessageDialogCtrl::init_(heap);
}

void ForkBeastGanonMessageDialogCtrl::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleMessageDialogCtrl::enter_(params);
}

void ForkBeastGanonMessageDialogCtrl::leave_() {
    SimpleMessageDialogCtrl::leave_();
}

void ForkBeastGanonMessageDialogCtrl::loadParams_() {
    SimpleMessageDialogCtrl::loadParams_();
    getAITreeVariable(&mGanonBeastVoiceSequenceCount_a, "GanonBeastVoiceSequenceCount");
    getAITreeVariable(&mInBeastGanonVoiceSequence_a, "InBeastGanonVoiceSequence");
}

void ForkBeastGanonMessageDialogCtrl::calc_() {
    SimpleMessageDialogCtrl::calc_();
}

}  // namespace uking::action
