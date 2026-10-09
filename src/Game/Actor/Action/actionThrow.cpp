#include "Game/Actor/Action/actionThrow.h"

namespace uking::action {

Throw::Throw(const InitArg& arg) : StopBase(arg) {}

Throw::~Throw() = default;

bool Throw::init_(sead::Heap* heap) {
    return StopBase::init_(heap);
}

void Throw::enter_(ksys::act::ai::InlineParamPack* params) {
    StopBase::enter_(params);
}

void Throw::leave_() {
    StopBase::leave_();
}

void Throw::loadParams_() {
    StopBase::loadParams_();
}

void Throw::calc_() {
    StopBase::calc_();
}

}  // namespace uking::action
