#include "Game/Actor/Action/actionForkBeastGanonMessageDialogCtrl.h"

namespace uking::action {

ForkBeastGanonMessageDialogCtrl::ForkBeastGanonMessageDialogCtrl(const InitArg& arg)
    : ForkBasicMessageDialogCtrl(arg) {}

ForkBeastGanonMessageDialogCtrl::~ForkBeastGanonMessageDialogCtrl() = default;

bool ForkBeastGanonMessageDialogCtrl::init_(sead::Heap* heap) {
    return ForkBasicMessageDialogCtrl::init_(heap);
}

void ForkBeastGanonMessageDialogCtrl::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkBasicMessageDialogCtrl::enter_(params);
}

void ForkBeastGanonMessageDialogCtrl::leave_() {
    ForkBasicMessageDialogCtrl::leave_();
}

void ForkBeastGanonMessageDialogCtrl::loadParams_() {
    ForkBasicMessageDialogCtrl::loadParams_();
    getAITreeVariable(&mGanonBeastVoiceSequenceCount_a, "GanonBeastVoiceSequenceCount");
    getAITreeVariable(&mInBeastGanonVoiceSequence_a, "InBeastGanonVoiceSequence");
}

void ForkBeastGanonMessageDialogCtrl::calc_() {
    ForkBasicMessageDialogCtrl::calc_();
}

}  // namespace uking::action
