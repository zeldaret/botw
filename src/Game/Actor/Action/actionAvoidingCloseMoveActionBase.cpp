#include "Game/Actor/Action/actionAvoidingCloseMoveActionBase.h"

namespace uking::action {

AvoidingCloseMoveActionBase::AvoidingCloseMoveActionBase(const InitArg& arg)
    : AvoidingCloseMoveBase(arg) {}

AvoidingCloseMoveActionBase::~AvoidingCloseMoveActionBase() = default;

bool AvoidingCloseMoveActionBase::init_(sead::Heap* heap) {
    return AvoidingCloseMoveBase::init_(heap);
}

void AvoidingCloseMoveActionBase::enter_(ksys::act::ai::InlineParamPack* params) {
    AvoidingCloseMoveBase::enter_(params);
}

void AvoidingCloseMoveActionBase::leave_() {
    AvoidingCloseMoveBase::leave_();
}

void AvoidingCloseMoveActionBase::loadParams_() {
    AvoidingCloseMoveBase::loadParams_();
}

void AvoidingCloseMoveActionBase::calc_() {
    AvoidingCloseMoveBase::calc_();
}

}  // namespace uking::action
