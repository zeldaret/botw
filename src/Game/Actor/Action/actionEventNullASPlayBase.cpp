#include "Game/Actor/Action/actionEventNullASPlayBase.h"

namespace uking::action {

EventNullASPlayBase::EventNullASPlayBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventNullASPlayBase::~EventNullASPlayBase() = default;

bool EventNullASPlayBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventNullASPlayBase::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS(mASName_d.cstr(), *mIsIgnoreSame_d, *mASSlot_d, *mSequenceBank_d, -1.0);
    mFlags.set(ksys::act::ai::Action::Flag::Changeable);
}

void EventNullASPlayBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventNullASPlayBase::loadParams_() {
    getDynamicParam(&mASSlot_d, "ASSlot");
    getDynamicParam(&mSequenceBank_d, "SequenceBank");
    getDynamicParam(&mIsIgnoreSame_d, "IsIgnoreSame");
    getDynamicParam(&mIsChangeable_d, "IsChangeable");
    getDynamicParam(&mASName_d, "ASName");
}

void EventNullASPlayBase::calc_() {
    if (!isFailed() && isFinishedAS(*mASSlot_d, *mSequenceBank_d)) {
        setFinished();
    }
}

}  // namespace uking::action
