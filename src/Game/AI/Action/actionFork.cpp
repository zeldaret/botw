#include "Game/AI/Action/actionFork.h"

namespace uking::action {

Fork::Fork(const InitArg& arg) : ksys::act::ai::Action(arg) {}

Fork::~Fork() = default;

bool Fork::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void Fork::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsChangeable_s)
        mFlags.set(Flag::_4);
}

void Fork::leave_() {
    ksys::act::ai::Action::leave_();
}

void Fork::loadParams_() {
    getStaticParam(&mEndState_s, "EndState");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
}

void Fork::calc_() {
    ksys::act::ai::Action::calc_();
}

void Fork::setEndState() {
    switch (*mEndState_s) {
    case 0:
        setFinished();
        break;
    case 1:
        setFailed();
        break;
    case 2:
        mFlags.set(ksys::act::ai::ActionBase::Flag::_4);
        break;
    }
}

}  // namespace uking::action
