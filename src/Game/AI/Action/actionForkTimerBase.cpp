#include "Game/AI/Action/actionForkTimerBase.h"

namespace uking::action {

ForkTimerBase::ForkTimerBase(const InitArg& arg) : Fork(arg) {}

ForkTimerBase::~ForkTimerBase() = default;

bool ForkTimerBase::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkTimerBase::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
}

void ForkTimerBase::leave_() {
    Fork::leave_();
}

void ForkTimerBase::loadParams_() {
    Fork::loadParams_();
}

void ForkTimerBase::calc_() {
    Fork::calc_();
}

}  // namespace uking::action
