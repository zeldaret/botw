#include "Game/AI/Action/actionMultiVacuumRotScaleTimeByDist.h"

namespace uking::action {

MultiVacuumRotScaleTimeByDist::MultiVacuumRotScaleTimeByDist(const InitArg& arg)
    : MultiVacuumRotScaleTimeByDistWithTgt(arg) {}

MultiVacuumRotScaleTimeByDist::~MultiVacuumRotScaleTimeByDist() = default;

bool MultiVacuumRotScaleTimeByDist::init_(sead::Heap* heap) {
    return MultiVacuumRotScaleTimeByDistWithTgt::init_(heap);
}

void MultiVacuumRotScaleTimeByDist::enter_(ksys::act::ai::InlineParamPack* params) {
    MultiVacuumRotScaleTimeByDistWithTgt::enter_(params);
}

void MultiVacuumRotScaleTimeByDist::leave_() {
    MultiVacuumRotScaleTimeByDistWithTgt::leave_();
}

void MultiVacuumRotScaleTimeByDist::loadParams_() {
    MultiVacuumRotScaleTimeByDistWithTgt::loadParams_();
    getStaticParam(&mMaxTimeDist_s, "MaxTimeDist");
}

void MultiVacuumRotScaleTimeByDist::calc_() {
    MultiVacuumRotScaleTimeByDistWithTgt::calc_();
}

}  // namespace uking::action
