#include "Game/Actor/Action/actionForkDynActorNoTargetSelf.h"

namespace uking::action {

ForkDynActorNoTargetSelf::ForkDynActorNoTargetSelf(const InitArg& arg)
    : ForkEndByConditionBase(arg) {}

ForkDynActorNoTargetSelf::~ForkDynActorNoTargetSelf() = default;

bool ForkDynActorNoTargetSelf::init_(sead::Heap* heap) {
    return ForkEndByConditionBase::init_(heap);
}

void ForkDynActorNoTargetSelf::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkEndByConditionBase::enter_(params);
}

void ForkDynActorNoTargetSelf::leave_() {
    ForkEndByConditionBase::leave_();
}

void ForkDynActorNoTargetSelf::loadParams_() {
    ForkEndByConditionBase::loadParams_();
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void ForkDynActorNoTargetSelf::calc_() {
    ForkEndByConditionBase::calc_();
}

}  // namespace uking::action
