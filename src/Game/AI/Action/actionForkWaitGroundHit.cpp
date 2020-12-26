#include "Game/AI/Action/actionForkWaitGroundHit.h"

namespace uking::action {

ForkWaitGroundHit::ForkWaitGroundHit(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkWaitGroundHit::~ForkWaitGroundHit() = default;

bool ForkWaitGroundHit::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkWaitGroundHit::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkWaitGroundHit::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkWaitGroundHit::loadParams_() {
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
}

void ForkWaitGroundHit::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
