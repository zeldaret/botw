#include "Game/AI/Action/actionGrab.h"

namespace uking::action {

Grab::Grab(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

bool Grab::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void Grab::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
}

void Grab::leave_() {
    ActionWithPosAngReduce::leave_();
}

void Grab::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mGrabIdx_s, "GrabIdx");
    getStaticParam(&mCheckRadius_s, "CheckRadius");
    getStaticParam(&mCheckSpeed_s, "CheckSpeed");
    getStaticParam(&mAttOffset_s, "AttOffset");
}

void Grab::calc_() {
    ActionWithPosAngReduce::calc_();
}

}  // namespace uking::action
