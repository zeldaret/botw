#include "Game/Actor/Action/actionAvoidingCloseMoveActionWithAcc.h"

namespace uking::action {

AvoidingCloseMoveActionWithAcc::AvoidingCloseMoveActionWithAcc(const InitArg& arg)
    : AvoidingCloseMoveBase(arg) {}

AvoidingCloseMoveActionWithAcc::~AvoidingCloseMoveActionWithAcc() = default;

bool AvoidingCloseMoveActionWithAcc::init_(sead::Heap* heap) {
    return AvoidingCloseMoveBase::init_(heap);
}

void AvoidingCloseMoveActionWithAcc::enter_(ksys::act::ai::InlineParamPack* params) {
    AvoidingCloseMoveBase::enter_(params);
}

void AvoidingCloseMoveActionWithAcc::leave_() {
    AvoidingCloseMoveBase::leave_();
}

void AvoidingCloseMoveActionWithAcc::loadParams_() {
    AvoidingCloseMoveBase::loadParams_();
    getStaticParam(&mAccRatio_s, "AccRatio");
}

void AvoidingCloseMoveActionWithAcc::calc_() {
    AvoidingCloseMoveBase::calc_();
}

}  // namespace uking::action
