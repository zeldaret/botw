#include "Game/Actor/Action/actionOnEnterSwapActorBase.h"

namespace uking::action {

OnEnterSwapActorBase::OnEnterSwapActorBase(const InitArg& arg) : Fork(arg) {}

OnEnterSwapActorBase::~OnEnterSwapActorBase() = default;

bool OnEnterSwapActorBase::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void OnEnterSwapActorBase::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
}

void OnEnterSwapActorBase::leave_() {
    Fork::leave_();
}

void OnEnterSwapActorBase::loadParams_() {
    Fork::loadParams_();
    getStaticParam(&mOnGroundPos_s, "OnGroundPos");
}

void OnEnterSwapActorBase::calc_() {
    Fork::calc_();
}

}  // namespace uking::action
