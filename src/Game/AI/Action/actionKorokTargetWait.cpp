#include "Game/AI/Action/actionKorokTargetWait.h"

namespace uking::action {

KorokTargetWait::KorokTargetWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

KorokTargetWait::~KorokTargetWait() = default;

bool KorokTargetWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void KorokTargetWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void KorokTargetWait::leave_() {
    ksys::act::ai::Action::leave_();
}

void KorokTargetWait::loadParams_() {
    getStaticParam(&mSpeedDecreRate_s, "SpeedDecreRate");
    getDynamicParam(&mDynStopTime_d, "DynStopTime");
}

void KorokTargetWait::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
