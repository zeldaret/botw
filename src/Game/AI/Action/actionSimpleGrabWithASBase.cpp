#include "Game/AI/Action/actionSimpleGrabWithASBase.h"

namespace uking::action {

SimpleGrabWithASBase::SimpleGrabWithASBase(const InitArg& arg) : Grab(arg) {}

SimpleGrabWithASBase::~SimpleGrabWithASBase() = default;

bool SimpleGrabWithASBase::init_(sead::Heap* heap) {
    return Grab::init_(heap);
}

void SimpleGrabWithASBase::enter_(ksys::act::ai::InlineParamPack* params) {
    Grab::enter_(params);
}

void SimpleGrabWithASBase::leave_() {
    Grab::leave_();
}

void SimpleGrabWithASBase::loadParams_() {
    Grab::loadParams_();
}

void SimpleGrabWithASBase::calc_() {
    Grab::calc_();
}

}  // namespace uking::action
