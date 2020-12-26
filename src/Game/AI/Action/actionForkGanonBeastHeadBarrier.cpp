#include "Game/AI/Action/actionForkGanonBeastHeadBarrier.h"

namespace uking::action {

ForkGanonBeastHeadBarrier::ForkGanonBeastHeadBarrier(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkGanonBeastHeadBarrier::~ForkGanonBeastHeadBarrier() = default;

bool ForkGanonBeastHeadBarrier::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkGanonBeastHeadBarrier::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkGanonBeastHeadBarrier::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkGanonBeastHeadBarrier::loadParams_() {
    getStaticParam(&mBarrierRad_s, "BarrierRad");
    getStaticParam(&mBarrierFront_s, "BarrierFront");
    getStaticParam(&mBarrierBack_s, "BarrierBack");
    getStaticParam(&mBarrierHeight_s, "BarrierHeight");
    getStaticParam(&mBarrierHeightMax_s, "BarrierHeightMax");
}

void ForkGanonBeastHeadBarrier::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
