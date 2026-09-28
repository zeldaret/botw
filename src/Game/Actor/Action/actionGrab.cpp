#include "Game/Actor/Action/actionGrab.h"

namespace uking::action {

Grab::Grab(const InitArg& arg) : StopBase(arg) {}

bool Grab::init_(sead::Heap* heap) {
    return StopBase::init_(heap);
}

void Grab::enter_(ksys::act::ai::InlineParamPack* params) {
    StopBase::enter_(params);
}

void Grab::leave_() {
    StopBase::leave_();
}

void Grab::loadParams_() {
    StopBase::loadParams_();
    getStaticParam(&mGrabIdx_s, "GrabIdx");
    getStaticParam(&mCheckRadius_s, "CheckRadius");
    getStaticParam(&mCheckSpeed_s, "CheckSpeed");
    getStaticParam(&mAttOffset_s, "AttOffset");
}

void Grab::calc_() {
    StopBase::calc_();
}

}  // namespace uking::action
