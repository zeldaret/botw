#include "Game/AI/Action/actionMoveToTargetBase.h"

namespace uking::action {

MoveToTargetBase::MoveToTargetBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

MoveToTargetBase::~MoveToTargetBase() = default;

bool MoveToTargetBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MoveToTargetBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void MoveToTargetBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void MoveToTargetBase::loadParams_() {
    getDynamicParam(&mDynTargetPos_d, "DynTargetPos");
    getDynamicParam(&mDynStartPos_d, "DynStartPos");
}

void MoveToTargetBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
