#include "Game/AI/Action/actionGrabRight.h"

namespace uking::action {

GrabRight::GrabRight(const InitArg& arg) : Grab(arg) {}

GrabRight::~GrabRight() = default;

bool GrabRight::init_(sead::Heap* heap) {
    return Grab::init_(heap);
}

void GrabRight::enter_(ksys::act::ai::InlineParamPack* params) {
    Grab::enter_(params);
}

void GrabRight::leave_() {
    Grab::leave_();
}

void GrabRight::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mGrabIdx_s, "GrabIdx");
    getStaticParam(&mCheckRadius_s, "CheckRadius");
    getStaticParam(&mCheckSpeed_s, "CheckSpeed");
    getStaticParam(&mAttOffset_s, "AttOffset");
}

void GrabRight::calc_() {
    Grab::calc_();
}

}  // namespace uking::action
