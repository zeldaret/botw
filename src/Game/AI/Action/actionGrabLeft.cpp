#include "Game/AI/Action/actionGrabLeft.h"

namespace uking::action {

GrabLeft::GrabLeft(const InitArg& arg) : Grab(arg) {}

GrabLeft::~GrabLeft() = default;

bool GrabLeft::init_(sead::Heap* heap) {
    return Grab::init_(heap);
}

void GrabLeft::enter_(ksys::act::ai::InlineParamPack* params) {
    Grab::enter_(params);
}

void GrabLeft::leave_() {
    Grab::leave_();
}

void GrabLeft::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mGrabIdx_s, "GrabIdx");
    getStaticParam(&mCheckRadius_s, "CheckRadius");
    getStaticParam(&mCheckSpeed_s, "CheckSpeed");
    getStaticParam(&mAttOffset_s, "AttOffset");
}

void GrabLeft::calc_() {
    Grab::calc_();
}

}  // namespace uking::action
