#include "Game/Actor/Action/actionForkBasicMessageDialogCtrl.h"

namespace uking::action {

ForkBasicMessageDialogCtrl::ForkBasicMessageDialogCtrl(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkBasicMessageDialogCtrl::~ForkBasicMessageDialogCtrl() = default;

bool ForkBasicMessageDialogCtrl::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkBasicMessageDialogCtrl::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkBasicMessageDialogCtrl::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkBasicMessageDialogCtrl::loadParams_() {
    getAITreeVariable(&mSimpleDialogUnit_a, "SimpleDialogUnit");
}

void ForkBasicMessageDialogCtrl::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
