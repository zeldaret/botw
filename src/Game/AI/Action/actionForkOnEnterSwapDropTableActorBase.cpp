#include "Game/AI/Action/actionForkOnEnterSwapDropTableActorBase.h"

namespace uking::action {

ForkOnEnterSwapDropTableActorBase::ForkOnEnterSwapDropTableActorBase(const InitArg& arg)
    : Fork(arg) {}

ForkOnEnterSwapDropTableActorBase::~ForkOnEnterSwapDropTableActorBase() = default;

bool ForkOnEnterSwapDropTableActorBase::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkOnEnterSwapDropTableActorBase::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
}

void ForkOnEnterSwapDropTableActorBase::leave_() {
    Fork::leave_();
}

void ForkOnEnterSwapDropTableActorBase::loadParams_() {
    Fork::loadParams_();
    getStaticParam(&mOnGroundPos_s, "OnGroundPos");
}

void ForkOnEnterSwapDropTableActorBase::calc_() {
    Fork::calc_();
}

}  // namespace uking::action
