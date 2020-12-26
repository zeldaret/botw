#include "Game/AI/Action/actionEventHoverNullASPlayBase.h"

namespace uking::action {

EventHoverNullASPlayBase::EventHoverNullASPlayBase(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventHoverNullASPlayBase::~EventHoverNullASPlayBase() = default;

bool EventHoverNullASPlayBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventHoverNullASPlayBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventHoverNullASPlayBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventHoverNullASPlayBase::loadParams_() {
    getDynamicParam(&mASSlot_d, "ASSlot");
    getDynamicParam(&mSequenceBank_d, "SequenceBank");
    getDynamicParam(&mIsIgnoreSame_d, "IsIgnoreSame");
    getDynamicParam(&mIsChangeable_d, "IsChangeable");
    getDynamicParam(&mASName_d, "ASName");
}

void EventHoverNullASPlayBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
