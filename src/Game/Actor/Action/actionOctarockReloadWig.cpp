#include "Game/Actor/Action/actionOctarockReloadWig.h"

namespace uking::action {

OctarockReloadWig::OctarockReloadWig(const InitArg& arg) : IgniteActorReloadBase(arg) {}

OctarockReloadWig::~OctarockReloadWig() = default;

bool OctarockReloadWig::init_(sead::Heap* heap) {
    return IgniteActorReloadBase::init_(heap);
}

void OctarockReloadWig::enter_(ksys::act::ai::InlineParamPack* params) {
    IgniteActorReloadBase::enter_(params);
}

void OctarockReloadWig::leave_() {
    IgniteActorReloadBase::leave_();
}

void OctarockReloadWig::loadParams_() {
    IgniteActorReloadBase::loadParams_();
    // FIXME: CALL _ZN4sead14SafeStringBaseIcEaSERKS1_ @ 0x7100b0caa0
    getAITreeVariable(&mOctarockFormChangeUnit_a, "OctarockFormChangeUnit");
}

void OctarockReloadWig::calc_() {
    IgniteActorReloadBase::calc_();
}

}  // namespace uking::action
