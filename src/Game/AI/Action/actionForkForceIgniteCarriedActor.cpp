#include "Game/AI/Action/actionForkForceIgniteCarriedActor.h"

namespace uking::action {

ForkForceIgniteCarriedActor::ForkForceIgniteCarriedActor(const InitArg& arg) : Fork(arg) {}

ForkForceIgniteCarriedActor::~ForkForceIgniteCarriedActor() = default;

bool ForkForceIgniteCarriedActor::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkForceIgniteCarriedActor::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
}

void ForkForceIgniteCarriedActor::leave_() {
    Fork::leave_();
}

void ForkForceIgniteCarriedActor::loadParams_() {
    Fork::loadParams_();
    getStaticParam(&mIsCheckAfterChildState_s, "IsCheckAfterChildState");
}

void ForkForceIgniteCarriedActor::calc_() {
    Fork::calc_();
}

}  // namespace uking::action
