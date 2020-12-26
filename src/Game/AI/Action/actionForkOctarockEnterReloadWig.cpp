#include "Game/AI/Action/actionForkOctarockEnterReloadWig.h"

namespace uking::action {

ForkOctarockEnterReloadWig::ForkOctarockEnterReloadWig(const InitArg& arg) : Fork(arg) {}

ForkOctarockEnterReloadWig::~ForkOctarockEnterReloadWig() = default;

bool ForkOctarockEnterReloadWig::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkOctarockEnterReloadWig::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
}

void ForkOctarockEnterReloadWig::leave_() {
    Fork::leave_();
}

void ForkOctarockEnterReloadWig::loadParams_() {
    Fork::loadParams_();
    // FIXME: CALL _ZN4sead14SafeStringBaseIcEaSERKS1_ @ 0x7100b0caa0
    getAITreeVariable(&mOctarockFormChangeUnit_a, "OctarockFormChangeUnit");
}

void ForkOctarockEnterReloadWig::calc_() {
    Fork::calc_();
}

}  // namespace uking::action
