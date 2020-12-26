#include "Game/AI/Action/actionSimpleMessageDialogCtrl.h"

namespace uking::action {

SimpleMessageDialogCtrl::SimpleMessageDialogCtrl(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SimpleMessageDialogCtrl::~SimpleMessageDialogCtrl() = default;

bool SimpleMessageDialogCtrl::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SimpleMessageDialogCtrl::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SimpleMessageDialogCtrl::leave_() {
    ksys::act::ai::Action::leave_();
}

void SimpleMessageDialogCtrl::loadParams_() {
    getAITreeVariable(&mSimpleDialogUnit_a, "SimpleDialogUnit");
}

void SimpleMessageDialogCtrl::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
