#include "Game/AI/Action/actionFork.h"

namespace uking::action {

Fork::Fork(const InitArg& arg) : ksys::act::ai::Action(arg) {}

Fork::~Fork() = default;

bool Fork::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void Fork::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
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

}  // namespace uking::action
