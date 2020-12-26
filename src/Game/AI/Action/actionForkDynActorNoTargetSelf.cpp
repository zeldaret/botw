#include "Game/AI/Action/actionForkDynActorNoTargetSelf.h"

namespace uking::action {

ForkDynActorNoTargetSelf::ForkDynActorNoTargetSelf(const InitArg& arg)
    : ForkDynActorNoTargetSelfBase(arg) {}

ForkDynActorNoTargetSelf::~ForkDynActorNoTargetSelf() = default;

bool ForkDynActorNoTargetSelf::init_(sead::Heap* heap) {
    return ForkDynActorNoTargetSelfBase::init_(heap);
}

void ForkDynActorNoTargetSelf::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkDynActorNoTargetSelfBase::enter_(params);
}

void ForkDynActorNoTargetSelf::leave_() {
    ForkDynActorNoTargetSelfBase::leave_();
}

void ForkDynActorNoTargetSelf::loadParams_() {
    ForkDynActorNoTargetSelfBase::loadParams_();
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void ForkDynActorNoTargetSelf::calc_() {
    ForkDynActorNoTargetSelfBase::calc_();
}

}  // namespace uking::action
