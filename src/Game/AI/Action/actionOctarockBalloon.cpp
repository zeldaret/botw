#include "Game/AI/Action/actionOctarockBalloon.h"

namespace uking::action {

OctarockBalloon::OctarockBalloon(const InitArg& arg) : OctarockBalloonBase(arg) {}

OctarockBalloon::~OctarockBalloon() = default;

bool OctarockBalloon::init_(sead::Heap* heap) {
    return OctarockBalloonBase::init_(heap);
}

void OctarockBalloon::enter_(ksys::act::ai::InlineParamPack* params) {
    OctarockBalloonBase::enter_(params);
}

void OctarockBalloon::leave_() {
    OctarockBalloonBase::leave_();
}

void OctarockBalloon::loadParams_() {
    OctarockBalloonBase::loadParams_();
    getStaticParam(&mTargetScale_s, "TargetScale");
    getStaticParam(&mStartSignTimer_s, "StartSignTimer");
    getStaticParam(&mStartASName_s, "StartASName");
    getStaticParam(&mSignASName_s, "SignASName");
}

void OctarockBalloon::calc_() {
    OctarockBalloonBase::calc_();
}

}  // namespace uking::action
