#include "Game/AI/Action/actionOctarockReloadWigBase.h"

namespace uking::action {

OctarockReloadWigBase::OctarockReloadWigBase(const InitArg& arg) : OnetimeStopASPlay(arg) {}

OctarockReloadWigBase::~OctarockReloadWigBase() = default;

bool OctarockReloadWigBase::init_(sead::Heap* heap) {
    return OnetimeStopASPlay::init_(heap);
}

void OctarockReloadWigBase::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
}

void OctarockReloadWigBase::leave_() {
    OnetimeStopASPlay::leave_();
}

void OctarockReloadWigBase::loadParams_() {
    OnetimeStopASPlay::loadParams_();
}

void OctarockReloadWigBase::calc_() {
    OnetimeStopASPlay::calc_();
}

}  // namespace uking::action
