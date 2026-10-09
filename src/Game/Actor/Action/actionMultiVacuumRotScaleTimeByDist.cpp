#include "Game/Actor/Action/actionMultiVacuumRotScaleTimeByDist.h"

namespace uking::action {

MultiVacuumRotScaleTimeByDist::MultiVacuumRotScaleTimeByDist(const InitArg& arg)
    : MultiVacuumRotBase(arg) {}

MultiVacuumRotScaleTimeByDist::~MultiVacuumRotScaleTimeByDist() = default;

bool MultiVacuumRotScaleTimeByDist::init_(sead::Heap* heap) {
    return MultiVacuumRotBase::init_(heap);
}

void MultiVacuumRotScaleTimeByDist::enter_(ksys::act::ai::InlineParamPack* params) {
    MultiVacuumRotBase::enter_(params);
}

void MultiVacuumRotScaleTimeByDist::leave_() {
    MultiVacuumRotBase::leave_();
}

void MultiVacuumRotScaleTimeByDist::loadParams_() {
    MultiVacuumRotBase::loadParams_();
    getStaticParam(&mMaxTimeDist_s, "MaxTimeDist");
}

void MultiVacuumRotScaleTimeByDist::calc_() {
    MultiVacuumRotBase::calc_();
}

}  // namespace uking::action
