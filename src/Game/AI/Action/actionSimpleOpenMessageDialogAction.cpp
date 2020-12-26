#include "Game/AI/Action/actionSimpleOpenMessageDialogAction.h"

namespace uking::action {

SimpleOpenMessageDialogAction::SimpleOpenMessageDialogAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SimpleOpenMessageDialogAction::~SimpleOpenMessageDialogAction() = default;

bool SimpleOpenMessageDialogAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SimpleOpenMessageDialogAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SimpleOpenMessageDialogAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void SimpleOpenMessageDialogAction::loadParams_() {
    getDynamicParam(&mMstxt_d, "Mstxt");
    getDynamicParam(&mLabel_d, "Label");
}

void SimpleOpenMessageDialogAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
