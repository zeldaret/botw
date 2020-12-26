#include "Game/AI/Action/actionForkDynActorNoTargetSelfBase.h"

namespace uking::action {

ForkDynActorNoTargetSelfBase::ForkDynActorNoTargetSelfBase(const InitArg& arg) : Fork(arg) {}

ForkDynActorNoTargetSelfBase::~ForkDynActorNoTargetSelfBase() = default;

bool ForkDynActorNoTargetSelfBase::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkDynActorNoTargetSelfBase::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
}

void ForkDynActorNoTargetSelfBase::leave_() {
    Fork::leave_();
}

void ForkDynActorNoTargetSelfBase::loadParams_() {
    Fork::loadParams_();
}

void ForkDynActorNoTargetSelfBase::calc_() {
    Fork::calc_();
}

}  // namespace uking::action
