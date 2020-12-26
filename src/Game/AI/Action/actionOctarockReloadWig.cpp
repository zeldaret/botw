#include "Game/AI/Action/actionOctarockReloadWig.h"

namespace uking::action {

OctarockReloadWig::OctarockReloadWig(const InitArg& arg) : OctarockReloadWigBase(arg) {}

OctarockReloadWig::~OctarockReloadWig() = default;

bool OctarockReloadWig::init_(sead::Heap* heap) {
    return OctarockReloadWigBase::init_(heap);
}

void OctarockReloadWig::enter_(ksys::act::ai::InlineParamPack* params) {
    OctarockReloadWigBase::enter_(params);
}

void OctarockReloadWig::leave_() {
    OctarockReloadWigBase::leave_();
}

void OctarockReloadWig::loadParams_() {
    OctarockReloadWigBase::loadParams_();
    // FIXME: CALL _ZN4sead14SafeStringBaseIcEaSERKS1_ @ 0x7100b0caa0
    getAITreeVariable(&mOctarockFormChangeUnit_a, "OctarockFormChangeUnit");
}

void OctarockReloadWig::calc_() {
    OctarockReloadWigBase::calc_();
}

}  // namespace uking::action
