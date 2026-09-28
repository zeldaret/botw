#include "Game/Actor/Action/actionOctarockBalloon.h"

namespace uking::action {

OctarockBalloon::OctarockBalloon(const InitArg& arg) : BalloonRopeBase(arg) {}

OctarockBalloon::~OctarockBalloon() = default;

bool OctarockBalloon::init_(sead::Heap* heap) {
    return BalloonRopeBase::init_(heap);
}

void OctarockBalloon::enter_(ksys::act::ai::InlineParamPack* params) {
    BalloonRopeBase::enter_(params);
}

void OctarockBalloon::leave_() {
    BalloonRopeBase::leave_();
}

void OctarockBalloon::loadParams_() {
    BalloonRopeBase::loadParams_();
    getStaticParam(&mTargetScale_s, "TargetScale");
    getStaticParam(&mStartSignTimer_s, "StartSignTimer");
    getStaticParam(&mStartASName_s, "StartASName");
    getStaticParam(&mSignASName_s, "SignASName");
}

void OctarockBalloon::calc_() {
    BalloonRopeBase::calc_();
}

}  // namespace uking::action
