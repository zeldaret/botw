#include "Game/Actor/Action/actionIgniteActorReloadBase.h"

namespace uking::action {

IgniteActorReloadBase::IgniteActorReloadBase(const InitArg& arg) : OnetimeStopASPlay(arg) {}

IgniteActorReloadBase::~IgniteActorReloadBase() = default;

bool IgniteActorReloadBase::init_(sead::Heap* heap) {
    return OnetimeStopASPlay::init_(heap);
}

void IgniteActorReloadBase::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
}

void IgniteActorReloadBase::leave_() {
    OnetimeStopASPlay::leave_();
}

void IgniteActorReloadBase::loadParams_() {
    OnetimeStopASPlay::loadParams_();
}

void IgniteActorReloadBase::calc_() {
    OnetimeStopASPlay::calc_();
}

}  // namespace uking::action
